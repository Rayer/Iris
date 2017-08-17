//
// Created by Rayer on 15/08/2017.
//

#ifndef IRIS_SPACE_H
#define IRIS_SPACE_H


#include <string>


class Space {
public:

    virtual std::string get_value(const std::string&& key) = 0;
    virtual void set_value(const std::string&& key, std::string value) = 0;

};
#endif //IRIS_SPACE_H
