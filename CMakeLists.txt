cmake_minimum_required(VERSION 3.6)
project(Iris)

set(CMAKE_CXX_STANDARD 11)
enable_testing(TRUE)

set(SOURCE_FILES main.cpp src/InventoryManager.cpp src/InventoryManager.h)
add_executable(Iris ${SOURCE_FILES})