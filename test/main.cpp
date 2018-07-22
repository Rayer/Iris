//
// Created by Rayer Tung on 2018/7/22.
//

// Because we uses our own environment, so we need to make our own test main
#include <cstdio>
#include <Logger/MasterLogger.h>
#include <Logger/SimpleConsoleLogger.h>

#include "gtest/gtest.h"

class TestingEnvironment : public testing::Environment {
public:
    void SetUp() override {
        Iris::MasterLogger::getLogger()->register_logger(std::make_shared<SimpleConsoleLogger>());
    }

    void TearDown() override {
    }
};


GTEST_API_ int main(int argc, char **argv) {
    printf("Running main() from gtest_main.cc\n");
    testing::AddGlobalTestEnvironment(new TestingEnvironment());
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
