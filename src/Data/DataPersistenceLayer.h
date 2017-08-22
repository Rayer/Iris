//
// Created by Rayer on 14/08/2017.
//

#ifndef IRIS_DATAPERSISTENCELAYER_H
#define IRIS_DATAPERSISTENCELAYER_H

#include <string>
#include <memory>
#include "Space.h"

/**
 * This is data persistance interface.
 * \author : Rayer
 */
class DataPersistenceLayer {
public:
    DataPersistenceLayer() = default;

    /**
     * Get Space(namespace)
     * \param name : Space Name
     * \return Shared pointer of a single Space
     */
    virtual std::shared_ptr<Space> get_space(const std::string &&name) = 0;

    /**
     *
     * @param id Space UUID
     * @return Shared pointer of a single Space
     */
    virtual std::shared_ptr<Space> get_space(long id) = 0;

    /**
     *
     */
    virtual ~DataPersistenceLayer() = default;
};

#endif //IRIS_DATAPERSISTENCELAYER_H
