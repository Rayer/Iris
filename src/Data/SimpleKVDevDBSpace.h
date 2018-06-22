//
// Created by Rayer on 15/08/2017.
//

#ifndef IRIS_SIMPLEDEVDBSPACE_H
#define IRIS_SIMPLEDEVDBSPACE_H


#include "KVSpace.h"
#include <map>
#include <boost/serialization/access.hpp>
#include <boost/serialization/map.hpp>
#include <list>

namespace Iris {
/**
 * DPL Space for development
 */
    class SimpleKVDevDBSpace : public KVSpace {

    private:
        std::map<std::string, ValueType> map;

    public:
        void serialize(std::string fullPath);

        void deserialize(std::string fullPath);

        ValueType get_value(const std::string &key) override;

        std::list<std::string> get_keys();

        void set_value(const std::string &key, const ValueType &value) override;

        bool remove(const std::string &key) override;

        void wipe() override;
    };

}
#endif //IRIS_SIMPLEDEVDBSPACE_H
