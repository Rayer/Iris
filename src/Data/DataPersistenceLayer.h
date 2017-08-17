//
// Created by Rayer on 14/08/2017.
//

#ifndef IRIS_DATAPERSISTENCELAYER_H
#define IRIS_DATAPERSISTENCELAYER_H

#include <string>
#include <memory>
#include "Space.h"

class DataPersistenceLayer {
public:
    DataPersistenceLayer() = default;

    virtual std::shared_ptr<Space> get_space(const std::string &&name) = 0;

    virtual std::shared_ptr<Space> get_space(long id) = 0;

    virtual ~DataPersistenceLayer() = default;
};

#endif //IRIS_DATAPERSISTENCELAYER_H
