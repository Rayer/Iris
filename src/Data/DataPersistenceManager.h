//
// Created by Rayer on 17/08/2017.
//

#ifndef IRIS_DATAPERSISTENCEMANAGER_H
#define IRIS_DATAPERSISTENCEMANAGER_H

class DataPersistenceLayer;

/**
 * Data Persistence Selector, will deliver different DPL implementation by compiling time
 */
class DataPersistenceManager {
private:
    static DataPersistenceLayer* dataPersistenceLayer;
    DataPersistenceManager() = default;
public:
    static DataPersistenceLayer* getInstance();

};


#endif //IRIS_DATAPERSISTENCEMANAGER_H
