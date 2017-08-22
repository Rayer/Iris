//
// Created by Rayer on 17/08/2017.
//

#include "DataPersistenceManager.h"
#include "SimpleDevDB.h"



DataPersistenceLayer* DataPersistenceManager::dataPersistenceLayer = nullptr;
//TODO: Add pre-compiler to determine debug and release for different instance....or load from file.
DataPersistenceLayer *DataPersistenceManager::getInstance() {
    if(dataPersistenceLayer == nullptr) {
        dataPersistenceLayer = new SimpleDevDB();
    }
    return dataPersistenceLayer;
}
