cmake_minimum_required(VERSION 3.6)
project(Iris)

set(CMAKE_CXX_STANDARD 11)
enable_testing()

# Boost dependency
# P.S. std::variant requires C++17, use boost::variant instead

FIND_PACKAGE(Boost REQUIRED serialization filesystem system log)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

# Not yet implemented
option(GRAPHIC_CLIENT "Build graphic client" OFF)

if(GRAPHIC_CLIENT)
    execute_process(COMMAND 'git submodule update cocos2d-x' .)
    add_subdirectory(deps/cocos2d-x)
endif(GRAPHIC_CLIENT)

add_subdirectory(deps/googletest)
add_subdirectory(test)
include_directories(deps/googletest/googletest/include)
include_directories(deps/googletest/googlemock/include)
include_directories(deps/mariadbpp/include)
include_directories(src)

set(GTEST_SRC_DIR deps/googletest/googletest)

add_subdirectory(deps/mariadbpp)
add_subdirectory(deps/mariadb-connector-c)


set(LIBS
        src/Data/KVDataPersistenceLayer.h
        src/Data/SimpleKVDevDB.cpp
        src/Data/SimpleKVDevDB.h
        src/Data/KVSpace.h
        src/Data/SimpleKVDevDBSpace.cpp
        src/Data/SimpleKVDevDBSpace.h
        src/Data/DataPersistenceManager.cpp
        src/Data/DataPersistenceManager.h
        src/Data/DataPersistenceManager.h
        src/Main/Context.cpp
        src/Main/Context.h
        src/Main/GameMain.cpp
        src/Main/GameMain.h
        src/Main/Iris_State.h
        src/Main/MoManager.cpp
        src/Main/MoManager.h
        src/Main/MoMLayer.h
        src/Main/Loopable.h
        src/Main/IDModule.h src/Data/SqlKVDatabase.cpp src/Data/SqlKVDatabase.h src/Data/SqlKVDatabaseSpace.cpp src/Data/SqlKVDatabaseSpace.h src/Exceptions/DPLException.cpp src/Exceptions/DPLException.h src/Exceptions/SqlException.cpp src/Exceptions/SqlException.h src/Utils/SqlCmd.cpp src/Utils/SqlCmd.h src/Logger/ILogger.h src/Logger/MasterLogger.cpp src/Logger/MasterLogger.h src/Logger/SimpleConsoleLogger.cpp src/Logger/SimpleConsoleLogger.h)

add_library(Iris_Libs ${LIBS})
add_executable(Iris main.cpp)