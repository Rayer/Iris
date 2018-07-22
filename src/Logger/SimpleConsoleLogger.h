//
// Created by Rayer Tung on 2018/7/21.
//

#ifndef IRIS_SIMPLECONSOLELOGGER_H
#define IRIS_SIMPLECONSOLELOGGER_H


#include "ILogger.h"

class SimpleConsoleLogger : public ILogger {
public:
    void warn(const std::string &msg) override;

    void error(const std::string &msg) override;

    void trace(const std::string &msg) override;

    void info(const std::string &msg) override;
};


#endif //IRIS_SIMPLECONSOLELOGGER_H
