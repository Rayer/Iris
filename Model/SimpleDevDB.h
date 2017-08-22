/**
 * Project Untitled
 */


#ifndef _SIMPLEDEVDB_H
#define _SIMPLEDEVDB_H

#include "DataAccessLayer.h"


class SimpleDevDB: public DataAccessLayer {
private: 
    map space_map;
};

#endif //_SIMPLEDEVDB_H