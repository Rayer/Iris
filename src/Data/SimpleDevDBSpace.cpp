//
// Created by Rayer on 15/08/2017.
//

#include "SimpleDevDBSpace.h"
#include <sstream>
#include <iostream>
#include <boost/serialization/variant.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>

using namespace Iris;

SimpleDevDBSpace::ValueType SimpleDevDBSpace::get_value(const std::string &&key) {
    return map.at(key);
}

void SimpleDevDBSpace::set_value(const std::string &&key, ValueType value) {
    map.insert({key, value});
}

void SimpleDevDBSpace::serialize(std::string fullPath) {
    std::ofstream ofs(fullPath);
    boost::archive::text_oarchive ar(ofs);
    ar << map;
    ofs.close();
}

void SimpleDevDBSpace::deserialize(std::string fullPath) {
    std::ifstream ifs(fullPath);
    boost::archive::text_iarchive ar(ifs);
    ar >> map;
    ifs.close();
}

std::list<std::string> SimpleDevDBSpace::get_keys() {
    std::list<std::string> ret;
    for (auto const &pair : map) {
        ret.push_back(pair.first);
    }
    return ret;
}
