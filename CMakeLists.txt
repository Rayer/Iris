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


set(SOURCE_FILES src/InventoryManager.cpp src/InventoryManager.h src/CharacterManager.cpp src/CharacterManager.h src/Data/DataPersistanceLayer.h)

add_executable(Iris ${SOURCE_FILES} main.cpp)
add_library(Iris_Libs ${SOURCE_FILES} main.cpp)
add_executable(Iris_Tests ${Source_FILES} test/CharacterManagerTest.cpp deps/googletest/googletest/src/gtest_main.cc test/DataPersistanceTest.cpp)
target_link_libraries(Iris_Tests gtest)