//
// Created by Rayer on 2018/6/19.
//

#ifndef IRIS_DPLEXCEPTION_H
#define IRIS_DPLEXCEPTION_H

#include <exception>

namespace Iris {
    class DPLException : public std::exception {
    protected:
        //Use this to
        std::string what_output;
        std::string reason;
        std::string driver_output;

    public:
        DPLException(const std::string &reason, const std::string &driver_output = "") noexcept;

        const char *what() const noexcept override;

        //Provide a noexcept copy constructor
        DPLException(const DPLException &) = default;

    public:
        ~DPLException() override = default;
    };
}


#endif //IRIS_DPLEXCEPTION_H
