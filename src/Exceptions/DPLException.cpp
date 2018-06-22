//
// Created by Rayer on 2018/6/19.
//

#include <string>
#include <boost/format.hpp>
#include "DPLException.h"

using namespace Iris;


const char *DPLException::what() const _NOEXCEPT {
    return what_output.c_str();
}

DPLException::DPLException(const std::string &reason, const std::string &driver_output) noexcept : std::exception() {
    this->reason = reason;
    this->driver_output = driver_output;
    boost::format output =
            boost::format("DPL Exception raised\nOS message : %1%\nreason : %2%\ndriver_output : %3%")
            % exception::what()
            % reason
            % driver_output;
    what_output = output.str();
}




