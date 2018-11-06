//
// Created by CORP\rayer on 10/31/18.
//

#ifndef IRIS_MYSQLPROVIDER_H
#define IRIS_MYSQLPROVIDER_H

#include "IDBEngineProvider.h"
#include <mysql++/mysql++.h>

namespace Iris {
    class MySqlProvider : public IDBEngineProvider {
        mysqlpp::Connection* conn;

    public:
        void connect(const std::string &ip, const std::string &user, const std::string &pass,
                             const std::string &database) override;

        std::shared_ptr<IQueryResult> query(const std::string &sql) override;

        std::shared_ptr<IExecuteResult> execute(const std::string &sql) override;

        void cleanup() override;
    };

    class MySqlQueryResult : public IQueryResult {
        mysqlpp::StoreQueryResult queryResult;
        mysqlpp::StoreQueryResult::const_iterator pos;
    public:
        std::string get_column(const std::string &column_name) override;

        unsigned long column_count() override;

        unsigned long row_count() override;

        bool next() override;

        bool prev() override;

        bool go_to_index(int index) override;

        std::string error() override;

        MySqlQueryResult(mysqlpp::StoreQueryResult queryResult);

        ~MySqlQueryResult() override;
    };

    class MySqlExecuteResult : public IExecuteResult {
        mysqlpp::SimpleResult execResult;
    public:
        MySqlExecuteResult(mysqlpp::SimpleResult execResult);
        bool result() override;

        std::string error() override;
    };
}

#endif //IRIS_MYSQLPROVIDER_H
