//
// Created by Rayer on 14/08/2017.
//

#ifndef IRIS_DATAPERSISTENCELAYER_H
#define IRIS_DATAPERSISTENCELAYER_H

#include <string>
#include <memory>
#include "KVSpace.h"

namespace Iris {


/**
 * This is data persistance interface.
 * \author : Rayer
 */
    class KVDataPersistenceLayer {
    public:
        KVDataPersistenceLayer() = default;

        /**
         * Get Space(namespace)
         * \param name : Space Name
         * \return Shared pointer of a single Space
         */
        virtual std::shared_ptr<KVSpace> get_space(const std::string &name) = 0;

        /**
         * Wipe all data
         */
        virtual void wipe(bool force) = 0;

        /**
         *
         */
        virtual ~KVDataPersistenceLayer() = default;


    };
}

#endif //IRIS_DATAPERSISTENCELAYER_H
