//
// Created by Rayer on 15/08/2017.
//

#include "SimpleDevDB.h"

std::shared_ptr<Space> SimpleDevDB::get_space(const std::string &&name) {
    auto iter = space_map.find(name);
    if(iter != space_map.end())
        return iter->second;

    std::shared_ptr<Space> space = std::make_shared<SimpleDevDBSpace>();
    space_map.insert(std::make_pair(name, space));
    return space;
}

std::shared_ptr<Space> SimpleDevDB::get_space(long id) {
    return nullptr;
}



