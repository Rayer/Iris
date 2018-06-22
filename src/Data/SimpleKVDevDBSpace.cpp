//
// Created by Rayer on 15/08/2017.
//

#include "SimpleKVDevDBSpace.h"
#include <sstream>
#include <iostream>
#include <boost/serialization/variant.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <fstream>

using namespace Iris;

SimpleKVDevDBSpace::ValueType SimpleKVDevDBSpace::get_value(const std::string &key) {
    return map.at(key);
}

void SimpleKVDevDBSpace::set_value(const std::string &key, const ValueType &value) {
    map.insert({key, value});
}

void SimpleKVDevDBSpace::serialize(std::string fullPath) {
    std::ofstream ofs(fullPath);
    boost::archive::text_oarchive ar(ofs);
    ar << map;
    ofs.close();
}

void SimpleKVDevDBSpace::deserialize(std::string fullPath) {
    std::ifstream ifs(fullPath);
    boost::archive::text_iarchive ar(ifs);
    ar >> map;
    ifs.close();
}

std::list<std::string> SimpleKVDevDBSpace::get_keys() {
    std::list<std::string> ret;
    for (auto const &pair : map) {
        ret.push_back(pair.first);
    }
    return ret;
}

bool SimpleKVDevDBSpace::remove(const std::string &key) {
    return map.erase(key) > 0;
}

void SimpleKVDevDBSpace::wipe() {

}
