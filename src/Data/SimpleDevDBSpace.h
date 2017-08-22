//
// Created by Rayer on 15/08/2017.
//

#ifndef IRIS_SIMPLEDEVDBSPACE_H
#define IRIS_SIMPLEDEVDBSPACE_H


#include "Space.h"
#include <map>

/**
 * DPL Space for development
 */
class SimpleDevDBSpace : public Space {
private:
    std::map<std::string, std::string> map;
public:
    std::string get_value(const std::string &&key) override;
    void set_value(const std::string &&key, std::string value) override;
};


#endif //IRIS_SIMPLEDEVDBSPACE_H
