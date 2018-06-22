//
// Created by Rayer on 2018/6/22.
//

#ifndef IRIS_SQLEXCEPTION_H
#define IRIS_SQLEXCEPTION_H

#include <string>
#include "DPLException.h"

namespace Iris {
    class SqlException : public DPLException {
        std::string sql;
    public:
        SqlException(const std::string &reason, const std::string &sql_command = "",
                     const std::string &driver_output = "") noexcept;

        const char *what() const noexcept override;

        ~SqlException() override = default;
    };
}


#endif //IRIS_SQLEXCEPTION_H
