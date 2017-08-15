//
// Created by Rayer on 15/08/2017.
//

#include "SimpleDevDB.h"

SimpleDevDBSpace *SimpleDevDB::get_space(const std::string &&name) {
    auto iter = space_map.find(name);
    if(iter != space_map.end())
        return iter->second;

    SimpleDevDBSpace* space = new SimpleDevDBSpace();
    space_map.insert(std::make_pair(name, space));
    return space;
}

SimpleDevDBSpace *SimpleDevDB::get_space(long id) {
    return nullptr;
}



