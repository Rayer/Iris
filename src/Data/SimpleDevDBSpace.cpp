//
// Created by Rayer on 15/08/2017.
//

#include "SimpleDevDBSpace.h"

std::string SimpleDevDBSpace::get_value(const std::string &&key) {
    return map.at(key);
}

void SimpleDevDBSpace::set_value(const std::string &&key, std::string value) {
    map.insert(std::make_pair(key, value));
}
