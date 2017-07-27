cmake_minimum_required(VERSION 3.6)
project(Iris)

set(CMAKE_CXX_STANDARD 11)
enable_testing()

add_subdirectory(deps/googletest)
include_directories(deps/googletest/googletest/include)
include_directories(deps/googletest/googlemock/include)


set(SOURCE_FILES src/InventoryManager.cpp src/InventoryManager.h test/test_main.cpp src/CharacterManager.cpp src/CharacterManager.h)

add_executable(Iris ${SOURCE_FILES} main.cpp)
add_library(Iris_Libs ${SOURCE_FILES} main.cpp)
add_executable(Iris_Tests ${Source_FILES} test/test_main.cpp)