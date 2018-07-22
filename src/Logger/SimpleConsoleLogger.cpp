//
// Created by Rayer Tung on 2018/7/21.
//

#include <iostream>
#include "SimpleConsoleLogger.h"

void SimpleConsoleLogger::warn(const std::string &msg) {
    std::cout << "WARN : " << msg << std::endl;
}

void SimpleConsoleLogger::error(const std::string &msg) {
    std::cout << "ERROR : " << msg << std::endl;
}

void SimpleConsoleLogger::trace(const std::string &msg) {
    std::cout << "TRACE : " << msg << std::endl;
}

void SimpleConsoleLogger::info(const std::string &msg) {
    std::cout << "INFO : " << msg << std::endl;
}
