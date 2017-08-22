cmake_minimum_required(VERSION 3.6)
project(Iris)

set(CMAKE_CXX_STANDARD 11)
enable_testing()
# Not yet implemented
option(GRAPHIC_CLIENT "Build graphic client" OFF)

if(GRAPHIC_CLIENT)
    execute_process(COMMAND 'git submodule update cocos2d-x' .)
    add_subdirectory(deps/cocos2d-x)
endif(GRAPHIC_CLIENT)

add_subdirectory(deps/googletest)
include_directories(deps/googletest/googletest/include)
include_directories(deps/googletest/googlemock/include)
include_directories(src)


set(LIBS
        src/InventoryManager.cpp
        src/InventoryManager.h
        src/CharacterManager.cpp
        src/CharacterManager.h
        src/Data/DataPersistenceLayer.h
        src/Data/SimpleDevDB.cpp
        src/Data/SimpleDevDB.h
        src/Data/Space.h
        src/Data/SimpleDevDBSpace.cpp
        src/Data/SimpleDevDBSpace.h
        src/Data/DataPersistenceManager.cpp
        src/Data/DataPersistenceManager.h)

add_executable(Iris ${LIBS} main.cpp)
add_library(Iris_Libs ${LIBS} main.cpp)
add_executable(Iris_Tests test/CharacterManagerTest.cpp deps/googletest/googletest/src/gtest_main.cc test/DataPersistanceTest.cpp)
target_link_libraries(Iris_Tests gtest Iris_Libs)