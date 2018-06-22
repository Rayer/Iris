//
// Created by Rayer on 17/08/2017.
//

#ifndef IRIS_DATAPERSISTENCEMANAGER_H
#define IRIS_DATAPERSISTENCEMANAGER_H

namespace Iris {

    class KVDataPersistenceLayer;

/**
 * Data Persistence Selector, will deliver different DPL implementation by compiling time
 */
    class DataPersistenceManager {
    private:
        static KVDataPersistenceLayer *dataPersistenceLayer;

        DataPersistenceManager() = default;

    public:
        static KVDataPersistenceLayer *getInstance();

    };
}

#endif //IRIS_DATAPERSISTENCEMANAGER_H
