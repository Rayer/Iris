//
// Created by Rayer Tung on 2018/7/21.
//

#ifndef IRIS_MASTERLOGGER_H
#define IRIS_MASTERLOGGER_H


#include "ILogger.h"
#include <memory>
#include <set>

namespace Iris {
    class MasterLogger : public ILogger {
    private:
        MasterLogger() = default;

        MasterLogger(const MasterLogger &) = default;

    protected:
        typedef std::shared_ptr<ILogger> LOG_SPEC;
        std::set<LOG_SPEC> m_loggers;
        static MasterLogger *m_inst;
    public:
        static MasterLogger *getLogger();

        virtual ~MasterLogger() = default;

        void register_logger(LOG_SPEC logger);

        void deregister_logger(LOG_SPEC logger);

        void warn(const std::string &msg) override;

        void error(const std::string &msg) override;

        void trace(const std::string &msg) override;

        void info(const std::string &msg) override;
    };
}


#endif //IRIS_MASTERLOGGER_H
