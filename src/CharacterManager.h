//
// Created by Rayer Tung on 27/07/2017.
//

#ifndef IRIS_CHARACTERMANAGER_H
#define IRIS_CHARACTERMANAGER_H


#include <string>

class CharInfo;

class CharSpec;

class CharacterManager {
public:
    std::shared_ptr<CharInfo *> get_main_char;

    std::shared_ptr<CharInfo *> get_char_by_spec(const CharSpec &charSpec);
};


#endif //IRIS_CHARACTERMANAGER_H
