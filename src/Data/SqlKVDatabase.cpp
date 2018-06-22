//
// Created by Rayer Tung on 2018/6/5.
//

#include "SqlKVDatabase.h"
#include "SqlKVDatabaseSpace.h"
#include <boost/format.hpp>
#include <Exceptions/SqlException.h>

using namespace Iris;
using namespace mariadb;

std::shared_ptr<KVSpace> SqlKVDatabase::get_space(const std::string &name) {

    //Find space map first
    if (m_space_map.find(name) != m_space_map.end())
        return m_space_map[name];

    std::string query = (
            boost::format("select 1 from information_schema.tables where table_schema='%1%' and table_name='%2%';") %
            m_db % name).str();
    result_set_ref result = m_con->query(query);

    if (result->row_count() == 0) {
        std::string sql = (boost::format("CREATE TABLE %1%\n"
                                         "(\n"
                                         "    `key` varchar(256) PRIMARY KEY NOT NULL,\n"
                                         "    value varchar(1024)\n"
                                         ");\n"
                                         "CREATE UNIQUE INDEX %1%_key_uindex ON %1% (`key`);") % name).str();
        if (m_con->execute(sql) == 0xffffffff) throw SqlException{"Fail to create in get_space", sql, m_con->error()};
    }

    std::shared_ptr<KVSpace> space = std::make_shared<SqlKVDatabaseSpace>(name, m_con);
    m_space_map.insert(std::make_pair(name, space));

    return space;
}

void SqlKVDatabase::wipe(bool force) {
    //TODO: Dangerous operation, need a WARN log
    std::string query = (
            boost::format("select TABLE_NAME from information_schema.tables where table_schema='%1%';") % m_db).str();
    result_set_ref result = m_con->query(query);

    while (result->next()) {
        m_con->execute((boost::format("drop table %1%;") % result->get_string("TABLE_NAME")).str());
    }


}

SqlKVDatabase::SqlKVDatabase(std::string host, std::string user, std::string pass, std::string database, long port) {

    m_account_setup = account::create(host, user, pass, database, (u32) port);
    m_db = database;
    m_account_setup->set_auto_commit(true);
    m_con = connection::create(m_account_setup);
    if (!m_con->connect()) throw SqlException{"Fail to initial SqlDataBase!", "", m_con->error()};
}

SqlKVDatabase::~SqlKVDatabase() {
    if (m_con) m_con->disconnect();
}
