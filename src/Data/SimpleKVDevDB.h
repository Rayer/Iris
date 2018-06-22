//
// Created by Rayer on 15/08/2017.
//

#ifndef IRIS_SIMPLEDEVDB_H
#define IRIS_SIMPLEDEVDB_H


#include "KVDataPersistenceLayer.h"
#include "SimpleKVDevDBSpace.h"
#include <boost/filesystem.hpp>

/**
 * DPL Implementation for development
 */

namespace Iris {
    class SimpleKVDevDB : public KVDataPersistenceLayer {
    protected:
        std::map<std::string, std::shared_ptr<SimpleKVDevDBSpace>> space_map;

    public:
        void serialize(std::string folder = boost::filesystem::complete(
                boost::filesystem::temp_directory_path()).generic_string());

        void deserialize(std::string folder = boost::filesystem::complete(
                boost::filesystem::temp_directory_path()).generic_string());

        std::shared_ptr<KVSpace> get_space(const std::string &name) override;

        void wipe(bool force) override;

        SimpleKVDevDB() = default;

        ~SimpleKVDevDB() = default;
    };

}
#endif //IRIS_SIMPLEDEVDB_H
