//
// Created by Rayer on 14/08/2017.
//

#ifndef IRIS_DATAPERSISTANCELAYER_H
#define IRIS_DATAPERSISTANCELAYER_H

#include <string>

class Space;
class DataPersistanceLayer {
public:
    virtual Space* get_space(const std::string name) = 0;
    virtual ~DataPersistanceLayer(){};
};
#endif //IRIS_DATAPERSISTANCELAYER_H
