set(TEST_HOSTNAME "localhost" CACHE STRING "Hostname for database")
set(TEST_PORT 3306 CACHE INTEGER "Port for database")
set(TEST_UNIXSOCKET "" CACHE STRING "Unix socket for database")
set(TEST_USERNAME "iris" CACHE STRING "User name for database")
set(TEST_PASSWORD "iris" CACHE STRING "Password for this account")
set(TEST_DATABASE "iris_test" CACHE STRING "Target schema/database")

configure_file(test_config.h.in test_config.h)

include_directories(../deps/googletest/googletest/include)
include_directories(../deps/googletest/googlemock/include)
include_directories(../deps/mariadbpp/include)
include_directories(../src)

set(TEST_FILES
        CharacterManagerTest.cpp
        SimpleKVDevDBTest.cpp
        ItemTest.cpp LoopSystemTest.cpp SqlKVDatabaseTest.cpp UtilSqlCmdTest.cpp main.cpp)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# message("${Boost_LIBRARIES} ${Boost_LIBRARY_DIR_RELEASE} ${Boost_LIBRARY_DIR_DEBUG} 123")

# add_executable(Iris ${LIBS} main.cpp)
add_executable(Iris_Tests main.cpp ${TEST_FILES})
target_link_libraries(Iris_Tests gtest Iris_Libs ${Boost_LIBRARIES} mariadbclientpp mariadbclient)