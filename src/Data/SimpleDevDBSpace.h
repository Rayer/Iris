//
// Created by Rayer on 15/08/2017.
//

#ifndef IRIS_SIMPLEDEVDBSPACE_H
#define IRIS_SIMPLEDEVDBSPACE_H


#include "Space.h"
#include <map>
#include <boost/serialization/access.hpp>
#include <boost/serialization/map.hpp>


/**
 * DPL Space for development
 */
class SimpleDevDBSpace : public Space {

private:
    std::map<std::string, ValueType> map;

public:
    void serialize(std::string fullPath);
    void deserialize(std::string fullPath);
    ValueType get_value(const std::string &&key) override;
    void set_value(const std::string &&key, ValueType value) override;
};


#endif //IRIS_SIMPLEDEVDBSPACE_H
