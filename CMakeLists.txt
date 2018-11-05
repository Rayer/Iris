cmake_minimum_required(VERSION 3.6)
project(Iris)

set(CMAKE_CXX_STANDARD 14)
enable_testing()

list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/cmake/")

# Boost dependency
# P.S. std::variant requires C++17, use boost::variant instead
set(BOOST_INCLUDEDIR )
FIND_PACKAGE(Boost REQUIRED serialization filesystem system)
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

FIND_PACKAGE(mysql++ REQUIRED)
INCLUDE_DIRECTORIES( ${mysql++_INCLUDE_DIR} )
add_definitions(-DMYSQLPP_MYSQL_HEADERS_BURIED)

# Not yet implemented
option(GRAPHIC_CLIENT "Build graphic client" OFF)

if(GRAPHIC_CLIENT)
    execute_process(COMMAND 'git submodule update cocos2d-x' .)
    add_subdirectory(deps/cocos2d-x)
endif(GRAPHIC_CLIENT)

add_subdirectory(deps/googletest)
include_directories(deps/googletest/googletest/include)
include_directories(deps/googletest/googlemock/include)
# include_directories(deps/mariadbpp/include)
include_directories(src)

set(GTEST_SRC_DIR deps/googletest/googletest)

# add_subdirectory(deps/mariadbpp)
# add_subdirectory(deps/mariadb-connector-c)


set(LIBS
        src/Data/KVDataPersistenceLayer.h
        src/Data/SimpleKVDevDB.cpp
        src/Data/SimpleKVDevDB.h
        src/Data/KVSpace.h
        src/Data/SimpleKVDevDBSpace.cpp
        src/Data/SimpleKVDevDBSpace.h
        src/Data/DataPersistenceManager.cpp
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
        src/Main/IDModule.h
        src/Data/SqlKVDatabase.cpp
        src/Data/SqlKVDatabase.h
        src/Data/SqlKVDatabaseSpace.cpp
        src/Data/SqlKVDatabaseSpace.h
        src/Exceptions/DPLException.cpp
        src/Exceptions/DPLException.h
        src/Exceptions/SqlException.cpp
        src/Exceptions/SqlException.h src/Utils/SqlCmd.cpp
        src/Utils/SqlCmd.h
        src/Data/DBEngine/IDBEngineProvider.h
        src/Data/DBEngine/MySqlProvider.cpp
        src/Data/DBEngine/MySqlProvider.h)

set(TEST_FILES
        test/CharacterManagerTest.cpp
        test/SimpleKVDevDBTest.cpp
        test/ItemTest.cpp test/LoopSystemTest.cpp test/SqlKVDatabaseTest.cpp test/UtilSqlCmdTest.cpp test/MySqlConnectorBasicTest.cpp)

# message("${Boost_LIBRARIES} ${Boost_LIBRARY_DIR_RELEASE} ${Boost_LIBRARY_DIR_DEBUG} 123")
# add_executable(Iris ${LIBS} main.cpp)
add_library(Iris_Libs ${LIBS})
add_executable(Iris_Tests deps/googletest/googletest/src/gtest_main.cc ${TEST_FILES})
target_link_libraries(Iris_Tests gtest Iris_Libs ${Boost_LIBRARIES} ${MYSQLPP_LIBRARIES})

