//
// Created by Rayer on 14/08/2017.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Data/SimpleDevDB.h>

class SimpleDevDB_Test : public ::testing::Test {

protected:
    DataPersistenceLayer* db;

    void SetUp() override {
        db = new SimpleDevDB();
    }

    void TearDown() override {
        delete db;
    }

};


TEST_F(SimpleDevDB_Test, SpaceAccessTest) {
    Space* space = db->get_space("ABC123");
    space->set_value("aaa", "1234");
    ASSERT_EQ(space->get_value("aaa"), "1234");
}

TEST_F(SimpleDevDB_Test, SpaceAccessTest2) {
    Space* space = db->get_space("ABC123");
    space->set_value("aaa", "1234");
    ASSERT_EQ(space->get_value("aaa"), "1234");
}