//
// Created by Rayer on 15/08/2017.
//

#ifndef IRIS_SIMPLEDEVDB_H
#define IRIS_SIMPLEDEVDB_H


#include "DataPersistenceLayer.h"
#include "SimpleDevDBSpace.h"
#include <boost/filesystem.hpp>

/**
 * DPL Implementation for development
 */

namespace Iris {
    class SimpleDevDB : public DataPersistenceLayer {
    protected:
        std::map<std::string, std::shared_ptr<SimpleDevDBSpace>> space_map;

    public:
        void serialize(std::string folder = boost::filesystem::complete(
                boost::filesystem::temp_directory_path()).generic_string());

        void deserialize(std::string folder = boost::filesystem::complete(
                boost::filesystem::temp_directory_path()).generic_string());

        std::shared_ptr<Space> get_space(const std::string &name) override;

        std::shared_ptr<Space> get_space(long id) override;


        void wipe(bool force) override;

        SimpleDevDB() = default;

        ~SimpleDevDB() = default;
    };

}
#endif //IRIS_SIMPLEDEVDB_H
