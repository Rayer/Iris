//
// Created by Rayer Tung on 2018/6/5.
//

#ifndef IRIS_SQLDATABASESPACE_H
#define IRIS_SQLDATABASESPACE_H

#include "KVSpace.h"
#include <map>
#include "DBEngine/IDBEngineProvider.h"

namespace Iris {
    class SqlKVDatabaseSpace : public KVSpace {
    private:
        std::map<std::string, ValueType> map;
        std::string space_name;
        IDBEngineProvider* sql_connect;

    public:
        SqlKVDatabaseSpace(const std::string &name, IDBEngineProvider *conn);

        ValueType get_value(const std::string &key) override;

        void set_value(const std::string &key, const ValueType &value) override;

        bool remove(const std::string &key) override;

        void wipe() override;

        void refresh();
    };
}




#endif //IRIS_SQLDATABASESPACE_H
