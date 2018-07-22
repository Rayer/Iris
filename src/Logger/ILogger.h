//
// Created by Rayer Tung on 2018/7/21.
//

#ifndef IRIS_ILOGGER_H
#define IRIS_ILOGGER_H

#include <string>

enum LogLevel {
    NONE,
    TRACE,
    INFO,
    WARN,
    ERROR
};

class ILogger {
public:
    virtual void notify_log_level_changed(LogLevel level) {};

    virtual void warn(const std::string &msg) = 0;

    virtual void error(const std::string &msg) = 0;

    virtual void trace(const std::string &msg) = 0;

    virtual void info(const std::string &msg) = 0;
};

#endif //IRIS_ILOGGER_H
