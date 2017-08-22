//
// Created by Rayer on 15/08/2017.
//

#ifndef IRIS_SPACE_H
#define IRIS_SPACE_H


#include <string>
#include <boost/variant.hpp>

/**
 * Space (Namespace) interface for DPL
 */
class Space {
public:
    typedef boost::variant<std::string, double, int> ValueType;
    virtual ValueType get_value(const std::string &&key) = 0;
    virtual void set_value(const std::string &&key, ValueType value) = 0;

};
#endif //IRIS_SPACE_H
