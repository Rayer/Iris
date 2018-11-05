//
// Created by Rayer Tung on 2018/6/5.
//

#include "SqlKVDatabase.h"
#include "SqlKVDatabaseSpace.h"
#include <boost/format.hpp>
#include <Exceptions/SqlException.h>
#include "Utils/SqlCmd.h"
#include "DBEngine/MySqlProvider.h"

using namespace Iris;
using namespace where_clause;

std::shared_ptr<KVSpace> SqlKVDatabase::get_space(const std::string &name) {

    //Find space map first
    if (m_space_map.find(name) != m_space_map.end())
        return m_space_map[name];

    //std::string sql_string = (
    //        boost::format("select 1 from information_schema.tables where table_schema='%1%' and table_name='%2%';") %
    //        m_db % name).str();
    std::string sql_string = SqlQuery("information_schema.tables").addQuery("1").where(
            Eq("table_schema", m_db) & Eq("table_name", name)).generate();

    try {
        //result_set_ref result = m_con->query(sql_string);
        QueryResult result = db->query(sql_string);

        if (result->row_count() == 0) {
            sql_string = (boost::format("CREATE TABLE %1%\n"
                                             "(\n"
                                             "    `key` varchar(256) PRIMARY KEY NOT NULL,\n"
                                             "    value varchar(1024)\n"
                                             ");\n"
                                             "CREATE UNIQUE INDEX %1%_key_uindex ON %1% (`key`);") % name).str();
            ExecuteResult exec_result = db->execute(sql_string);
            if (!exec_result) throw SqlException{"Fail to create in get_space", sql_string, exec_result->error()};
        }

        std::shared_ptr<KVSpace> space = std::make_shared<SqlKVDatabaseSpace>(name, db);
        m_space_map.insert(std::make_pair(name, space));

        return space;
    }  catch(Iris::DPLException& dpl) {
        throw dpl;
    }

}

void SqlKVDatabase::wipe(bool force) {
    //TODO: Dangerous operation, need a WARN log
    //std::string sql_String = (
    //        boost::format("select TABLE_NAME from information_schema.tables where table_schema='%1%';") % m_db).str();
    std::string sql_String = SqlQuery("information_schema.tables").addQuery("TABLE_NAME").where(
            Eq("table_schema", m_db)).generate();

    QueryResult result = db->query(sql_String);

    while (result->next()) {
        db->execute((boost::format("drop table %1%;") % result->get_column("TABLE_NAME")).str());
    }


}

SqlKVDatabase::SqlKVDatabase(const std::string &host, const std::string &user, const std::string &pass,
                             const std::string &database, long port) {
    db = new MySqlProvider();
}

SqlKVDatabase::~SqlKVDatabase() {
    if (db) db->cleanup();
}
