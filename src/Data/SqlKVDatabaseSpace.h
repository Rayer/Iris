//
// Created by Rayer Tung on 2018/6/5.
//

#ifndef IRIS_SQLDATABASESPACE_H
#define IRIS_SQLDATABASESPACE_H

#include "KVSpace.h"
#include <mariadb++/connection.hpp>

namespace Iris {
    class SqlKVDatabaseSpace : public KVSpace {
    private:
        std::map<std::string, ValueType> map;
        std::string space_name;
        mariadb::result_set_ref cached_context;
        mariadb::connection_ref sql_connect;
    public:
        SqlKVDatabaseSpace(const std::string &name, mariadb::connection_ref conn);

        ValueType get_value(const std::string &key) override;

        void set_value(const std::string &key, const ValueType &value) override;

        bool remove(const std::string &key) override;

        void wipe() override;

        void refresh();
    };
}




#endif //IRIS_SQLDATABASESPACE_H
