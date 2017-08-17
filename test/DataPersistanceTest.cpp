//
// Created by Rayer on 14/08/2017.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Data/SimpleDevDB.h>
#include <Data/DataPersistenceManager.h>
#include <iostream>

class SimpleDevDB_Test : public ::testing::Test {

protected:
    DataPersistenceLayer* db;

    void SetUp() override {
        //std::cout << "Setup()" << std::endl;
        db = DataPersistenceManager::getInstance();
    }

    void TearDown() override {
        //std::cout << "TearDown()" << std::endl;
        //Don't delete because it is singleton
        //delete db;
    }

};


TEST_F(SimpleDevDB_Test, SpaceAccessTest) {
    std::shared_ptr<Space> space = db->get_space("ABC123");
    space->set_value("aaa", "1234");
    ASSERT_EQ(space->get_value("aaa"), "1234");
}

TEST_F(SimpleDevDB_Test, SpaceAccessReferenceTest) {
    std::shared_ptr<Space> space = db->get_space("AAA");
    space->set_value("aaa", "1234");
    std::shared_ptr<Space> space2 = db->get_space("AAA");
    ASSERT_EQ(space2->get_value("aaa"), "1234");
}

TEST_F(SimpleDevDB_Test, SpaceGetNilValueTest) {
    std::shared_ptr<Space> space = db->get_space("Test1");
    ASSERT_ANY_THROW(space->get_value("AAA"));
}

TEST_F(SimpleDevDB_Test, SpaceKeyRemovalTest) {

}


TEST_F(SimpleDevDB_Test, SpaceRedefineKeyValueTest) {

}
