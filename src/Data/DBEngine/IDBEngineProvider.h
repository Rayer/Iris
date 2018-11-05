//
// Created by CORP\rayer on 10/31/18.
//

#ifndef IRIS_IDBENGINE_H
#define IRIS_IDBENGINE_H

#include <string>
#include <memory>


namespace Iris {
    class IQueryResult;
    class IExecuteResult;

    typedef std::shared_ptr<IQueryResult> QueryResult;
    typedef std::shared_ptr<IExecuteResult> ExecuteResult;

    class IDBEngineProvider {
    public:


        // A factory might be a better idea... but let's start by this first.
        virtual void connect(const std::string &ip, const std::string &user, const std::string &pass,
                             const std::string &database) = 0;
        virtual QueryResult query(const std::string& sql) = 0;
        virtual ExecuteResult execute(const std::string& sql) = 0;
        virtual void cleanup() = 0;
        virtual ~IDBEngineProvider() = default;
    };

    class IQueryResult {
    public:
        virtual std::string get_column(const std::string& column_name) = 0;
        virtual unsigned long column_count() = 0;
        virtual unsigned long row_count() = 0;
        virtual bool next() = 0;
        virtual bool prev() = 0;
        virtual bool go_to_index(int index) = 0;
        virtual std::string error() = 0;
        virtual ~IQueryResult() = default;
    };

    class IExecuteResult {
    public:
        virtual bool result() = 0;
        virtual std::string error() = 0;
        virtual ~IExecuteResult() = default;
    };
}



#endif //IRIS_IDBENGINE_H
