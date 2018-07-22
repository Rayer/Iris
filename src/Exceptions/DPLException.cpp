//
// Created by Rayer on 2018/6/19.
//

#include <string>
#include <boost/format.hpp>
#include "DPLException.h"

using namespace Iris;


const char *DPLException::what() const noexcept {
    return what_output.c_str();
}

//This wrapped_exception will cause unnecessery copy....
//But wrapped exception cant be reference, hence wrapped exception will be out of scope and invalid soon.
DPLException::DPLException(const std::string &reason, const std::string &driver_output) noexcept : wrapped_exception(*this), std::exception() {
    what_output = generate_message(reason, driver_output);
}

std::string DPLException::generate_message(const std::string &reason, const std::string &driver_output) {
    DPLException::reason = reason;
    DPLException::driver_output = driver_output;
    boost::format output =
            boost::format("DPL Exception raised\nOS message : %1%\nreason : %2%\ndriver_output : %3%\n")
            % wrapped_exception.what()
            % reason
            % driver_output;
    return output.str();
}

DPLException::DPLException(const std::exception &wrapped, const std::string &reason,
                           const std::string &driver_output) noexcept : wrapped_exception(wrapped), std::exception()  {

}



