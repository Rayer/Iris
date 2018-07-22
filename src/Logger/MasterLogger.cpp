//
// Created by Rayer Tung on 2018/7/21.
//

#include "MasterLogger.h"

using namespace Iris;

MasterLogger *MasterLogger::m_inst;

void MasterLogger::warn(const std::string &msg) {
    for (const LOG_SPEC &logger : m_loggers) {
        logger->warn(msg);
    }
}

void MasterLogger::error(const std::string &msg) {
    for (const LOG_SPEC &logger : m_loggers) {
        logger->error(msg);
    }
}

void MasterLogger::trace(const std::string &msg) {
    for (const LOG_SPEC &logger : m_loggers) {
        logger->trace(msg);
    }
}

void MasterLogger::info(const std::string &msg) {
    for (const LOG_SPEC &logger : m_loggers) {
        logger->info(msg);
    }
}

void MasterLogger::register_logger(std::shared_ptr<ILogger> logger) {
    m_loggers.insert(logger);
}

void MasterLogger::deregister_logger(std::shared_ptr<ILogger> logger) {

}

MasterLogger *MasterLogger::getLogger() {
    if (!m_inst) {
        m_inst = new MasterLogger();
    }
    return m_inst;
}
