//
// Created by Rayer on 15/08/2017.
//

#ifndef IRIS_SIMPLEDEVDB_H
#define IRIS_SIMPLEDEVDB_H


#include "DataPersistenceLayer.h"
#include "SimpleDevDBSpace.h"

class SimpleDevDB : public DataPersistenceLayer {
protected:
    std::map<std::string, SimpleDevDBSpace*> space_map;
public:
    SimpleDevDBSpace *get_space(const std::string &&name) override;
    SimpleDevDBSpace *get_space(long id) override;

    SimpleDevDB() = default;
    ~SimpleDevDB() = default;
};


#endif //IRIS_SIMPLEDEVDB_H
