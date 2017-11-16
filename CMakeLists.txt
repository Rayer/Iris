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
include_directories(deps/googletest/googletest/include)
include_directories(deps/googletest/googlemock/include)
include_directories(src)


set(LIBS
        src/Data/DataPersistenceLayer.h
        src/Data/SimpleDevDB.cpp
        src/Data/SimpleDevDB.h
        src/Data/Space.h
        src/Data/SimpleDevDBSpace.cpp
        src/Data/SimpleDevDBSpace.h
        src/Data/DataPersistenceManager.cpp
<<<<<<< HEAD
        src/Data/DataPersistenceManager.h src/Utils/Logger.cpp src/Utils/Logger.h)
=======
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
        src/Main/IDModule.h)
>>>>>>> master

set(TEST_FILES
        test/CharacterManagerTest.cpp
        test/DataPersistanceTest.cpp
        test/ItemTest.cpp test/LoopSystemTest.cpp)

message("${Boost_LIBRARIES} ${Boost_LIBRARY_DIR_RELEASE} ${Boost_LIBRARY_DIR_DEBUG} 123")

# add_executable(Iris ${LIBS} main.cpp)
add_library(Iris_Libs ${LIBS})
add_executable(Iris_Tests deps/googletest/googletest/src/gtest_main.cc ${TEST_FILES})
target_link_libraries(Iris_Tests gtest Iris_Libs ${Boost_LIBRARIES} )