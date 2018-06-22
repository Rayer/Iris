//
// Created by Rayer Tung on 2018/6/5.
//

#include "SqlKVDatabaseSpace.h"
#include <boost/format.hpp>
#include "Exceptions/SqlException.h"
#include <boost/serialization/variant.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace mariadb;

Iris::KVSpace::ValueType Iris::SqlKVDatabaseSpace::get_value(const std::string &key) {

    std::string query = (boost::format("select `value` from %1% where `key`='%2%'") % space_name % key).str();
    result_set_ref result = sql_connect->query(query);
    if (result->row_count() == 0) throw SqlException{"get_value not found key!", query, sql_connect->error()};

    result->next();
    std::string data = result->get_string("value");

    ValueType ret;
    std::stringstream ss;
    ss << data;
    boost::archive::text_iarchive ar(ss);
    ar >> ret;

    return ret;
}

void Iris::SqlKVDatabaseSpace::set_value(const std::string &key, const Iris::KVSpace::ValueType &value) {
    //Find if key exist. If key exist, use update, then insert.
    u32 index = cached_context->column_index(key);
    //if not found, index will be 0xffffffff..er.. in fact, it's -1
    bool update = index != 0xffffffff;

    std::stringstream blob;
    boost::archive::text_oarchive ar(blob);
    ar << value;

    static boost::format update_string = boost::format("update %1% set `value` = '%3%' where `key` = '%2%';");
    static boost::format insert_string = boost::format("insert into `%1%` (`key`, `value`) values ('%2%','%3%');");
    std::string sql = ((update ? update_string : insert_string) % space_name % key % blob.str()).str();
    if (!sql_connect->execute(sql)) throw SqlException{"set_value failed" + sql, sql_connect->error()};
}

Iris::SqlKVDatabaseSpace::SqlKVDatabaseSpace(const std::string &name, mariadb::connection_ref conn) {
    space_name = name;
    cached_context = conn->query(
            (boost::format("select * from %1% where 1=1") % name).str());
    this->sql_connect = conn;
}

bool Iris::SqlKVDatabaseSpace::remove(const std::string &key) {
    return false;
}

void Iris::SqlKVDatabaseSpace::wipe() {
    std::string sql_string = (boost::format("drop table %1%;") % space_name).str();
    if (!sql_connect->execute(sql_string)) throw SqlException{"wipe failed", sql_string, sql_connect->error()};
}

void Iris::SqlKVDatabaseSpace::refresh() {

}
