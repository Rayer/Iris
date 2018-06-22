//
// Created by Rayer on 15/08/2017.
//

#include <sstream>
#include <boost/filesystem.hpp>
#include "SimpleKVDevDB.h"

using namespace boost::filesystem;
using namespace Iris;

std::shared_ptr<KVSpace> SimpleKVDevDB::get_space(const std::string &name) {
    auto iter = space_map.find(name);
    if (iter != space_map.end())
        return iter->second;

    std::shared_ptr<SimpleKVDevDBSpace> space = std::make_shared<SimpleKVDevDBSpace>();
    space_map.insert({name, space});
    return space;
}


void SimpleKVDevDB::serialize(std::string folder) {
    //Create folder if not exist
    boost::filesystem::create_directory(folder);
    for (auto iter : space_map) {
        const std::string &space_name = iter.first;
        std::ostringstream ss;
        ss << folder << "/" << space_name << ".sel";
        std::static_pointer_cast<SimpleKVDevDBSpace>(iter.second)->serialize(ss.str());
    }
}

void SimpleKVDevDB::deserialize(std::string folder) {
    path p(folder);

    if (!is_directory(p)) throw ("Illegal deserialize folder name");
    std::list<path> list;
    std::copy(directory_iterator(p), directory_iterator(), std::back_inserter(list));

    for (auto &file : list) {
        if (file.extension().generic_string() != ".sel") continue;
        std::shared_ptr<SimpleKVDevDBSpace> space = std::make_shared<SimpleKVDevDBSpace>();
        space->deserialize(complete(file).generic_string());
        space_map.insert(std::make_pair(file.stem().generic_string(), space));
    }

}

void SimpleKVDevDB::wipe(bool force) {
    space_map.clear();
}





