//
// Created by Rayer on 2018/6/22.
//

#include "SqlException.h"
#include <boost/format.hpp>


const char *Iris::SqlException::what() const noexcept {
    return what_output.c_str();
}



Iris::SqlException::SqlException(const std::string &reason, const std::string &sql_command,
                                 const std::string &driver_output) noexcept : DPLException(reason, driver_output) {
    what_output = generate_message(reason, sql_command, driver_output);
}

Iris::SqlException::SqlException(const std::exception &wrapped, const std::string &reason,
                                 const std::string &sql_command, const std::string &driver_output) noexcept : DPLException(wrapped, reason, driver_output) {
    what_output = generate_message(reason, sql_command, driver_output);
}

std::string Iris::SqlException::generate_message(const std::string &reason, const std::string &sql_command,
                                    const std::string &driver_output) {
    this->sql = sql_command;
    boost::format output =
            boost::format(
                    "\nSQL Exception raised\nOS message : %1%\nsql_command : %2%\nreason : %3%\ndriver_output : %4%\n")
            %
            wrapped_exception.what() //Don't use what(), it will cause loop. Dont use DPLException::what() too, will include duplicated message
            % this->sql
            % reason
            % driver_output;
    return output.str();
}




