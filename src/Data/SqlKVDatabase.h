//
// Created by Rayer Tung on 2018/6/5.
//

#ifndef IRIS_SQLDATABASE_H
#define IRIS_SQLDATABASE_H

#include "KVDataPersistenceLayer.h"
#include "DBEngine/IDBEngineProvider.h"
#include <map>

namespace Iris {
    class SqlKVDatabase : public KVDataPersistenceLayer {

        IDBEngineProvider* db;
        std::string m_dbName;
        std::map<std::string, std::shared_ptr<KVSpace> > m_space_map;

    public:
        SqlKVDatabase(const std::string &host, const std::string &user, const std::string &pass,
                      const std::string &database, long port = 3306);

        ~SqlKVDatabase() override;

        std::shared_ptr<KVSpace> get_space(const std::string &name) override;
        void wipe(bool force) override;
    };


}



#endif //IRIS_SQLDATABASE_H
