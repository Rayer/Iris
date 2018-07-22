//
// Created by Rayer Tung on 2018/6/5.
//

#ifndef IRIS_SQLDATABASE_H
#define IRIS_SQLDATABASE_H

#include "KVDataPersistenceLayer.h"
#include <mariadb++/connection.hpp>

namespace Iris {
    class SqlKVDatabase : public KVDataPersistenceLayer {

        mariadb::account_ref m_account_setup;
        std::string m_db;
        mariadb::connection_ref m_con;
        std::map<std::string, std::shared_ptr<KVSpace> > m_space_map;

    public:
        SqlKVDatabase(const std::string &host, const std::string &user, const std::string &pass,
                      const std::string &database, const std::string &unix_socket, long port);

        ~SqlKVDatabase() override;

        std::shared_ptr<KVSpace> get_space(const std::string &name) override;
        void wipe(bool force) override;
    };


}



#endif //IRIS_SQLDATABASE_H
