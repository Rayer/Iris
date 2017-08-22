//
// Created by Rayer on 15/08/2017.
//

#ifndef IRIS_SIMPLEDEVDB_H
#define IRIS_SIMPLEDEVDB_H


#include "DataPersistenceLayer.h"
#include "SimpleDevDBSpace.h"

/**
 * DPL Implementation for development
 */
class SimpleDevDB : public DataPersistenceLayer {
protected:
    std::map<std::string, std::shared_ptr<Space>> space_map;
public:
    std::shared_ptr<Space> get_space(const std::string &&name) override;
    std::shared_ptr<Space> get_space(long id) override;

    SimpleDevDB() = default;
    ~SimpleDevDB() = default;
};


#endif //IRIS_SIMPLEDEVDB_H
