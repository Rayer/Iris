//
// Created by Rayer Tung on 2018/6/5.
//

#include "SqlKVDatabaseSpace.h"
#include <boost/format.hpp>
#include "Exceptions/SqlException.h"
#include <boost/serialization/variant.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <mariadb++/exceptions.hpp>
#include "Utils/SqlCmd.h"

using namespace mariadb;
using namespace where_clause;

Iris::KVSpace::ValueType Iris::SqlKVDatabaseSpace::get_value(const std::string &key) {

    //std::string sql_string = (boost::format("select `value` from %1% where `key`='%2%'") % space_name % key).str();
    std::string sql_string = SqlQuery(space_name).addQuery("`value`").where(Eq("`key`", key)).generate();

    try {
        result_set_ref result = sql_connect->query(sql_string);
        if (result->row_count() == 0) throw SqlException{"get_value not found key!", sql_string, sql_connect->error()};

        result->next();
        std::string data = result->get_string("value");

        ValueType ret;
        std::stringstream ss;
        ss << data;
        boost::archive::text_iarchive ar(ss);
        ar >> ret;

        return ret;
    } catch(mariadb::exception::base& ex) {

        //wrap up as DPL/SQL exceptions

        throw SqlException{ex, "set_value", sql_string, sql_connect->error()};

    } catch(Iris::DPLException& dpl) {
        throw dpl;
    }

}

void Iris::SqlKVDatabaseSpace::set_value(const std::string &key, const Iris::KVSpace::ValueType &value) {

    //Use sql_string on demend....
    //std::string sql_string = (boost::format("select 1 from %1% where `key` = '%2%';") % space_name % key).str();
    std::string sql_string = SqlQuery(space_name).addQuery("1").where(Eq("`key`", key)).generate();
    try {
        sql_connect->query(sql_string);
        bool update = 0 != sql_connect->query(sql_string)->row_count();

        std::stringstream blob;
        boost::archive::text_oarchive ar(blob);
        ar << value;

        //static boost::format update_string = boost::format("update `%1%` set `value` = '%3%' where `key` = '%2%';");
        //static boost::format insert_string = boost::format("insert into `%1%` (`key`, `value`) values ('%2%','%3%');");
        //sql_string = ((update ? update_string : insert_string) % space_name % key % blob.str()).str();
        if (update) {
            sql_string = SqlUpdate(space_name).setValue("`value`", blob.str()).where(Eq("`key`", key)).generate();
        } else {
            sql_string = SqlInsert(space_name).insertValue("`key`", key).insertValue("`value`", blob.str()).generate();
        }
        if (!sql_connect->execute(sql_string)) throw SqlException{"set_value failed", sql_string, sql_connect->error()};
    } catch(mariadb::exception::base& ex) {

        //wrap up as DPL/SQL exceptions

        throw SqlException{ex, "set_value", sql_string, sql_connect->error()};

    } catch(Iris::DPLException& dpl) {
        throw dpl;
    }


}

Iris::SqlKVDatabaseSpace::SqlKVDatabaseSpace(const std::string &name, mariadb::connection_ref conn) {
    space_name = name;
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
    //not used now.
}
