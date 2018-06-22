//
// Created by Rayer on 17/08/2017.
//

#include "DataPersistenceManager.h"
#include "SimpleKVDevDB.h"

using namespace Iris;


KVDataPersistenceLayer *DataPersistenceManager::dataPersistenceLayer = nullptr;

//TODO: Add pre-compiler to determine debug and release for different instance....or load from file.
KVDataPersistenceLayer *DataPersistenceManager::getInstance() {
    if (dataPersistenceLayer == nullptr) {
        dataPersistenceLayer = new SimpleKVDevDB();
    }
    return dataPersistenceLayer;
}

