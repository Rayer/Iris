//
// Created by Rayer on 14/08/2017.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Data/SimpleDevDB.h>
#include <Data/DataPersistenceManager.h>

using namespace Iris;

class SimpleDevDB_Test : public ::testing::Test {

protected:
    DataPersistenceLayer *db;


    void SetUp() override {
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
    EXPECT_EQ(boost::get<std::string>(space->get_value("aaa")), "1234");
    space->set_value("bbb", 1234);
    EXPECT_EQ(boost::get<int>(space->get_value("bbb")), 1234);
}

TEST_F(SimpleDevDB_Test, SpaceAccessReferenceTest) {
    std::shared_ptr<Space> space = db->get_space("AAA");
    space->set_value("aaa", "1234");
    std::shared_ptr<Space> space2 = db->get_space("AAA");
    ASSERT_EQ(boost::get<std::string>(space2->get_value("aaa")), "1234");
}

TEST_F(SimpleDevDB_Test, SpaceGetNilValueTest) {
    std::shared_ptr<Space> space = db->get_space("Test1");
    ASSERT_ANY_THROW(space->get_value("AAA"));
}


TEST_F(SimpleDevDB_Test, SpaceSerializeTest) {
    std::shared_ptr<Space> space1 = db->get_space("AAA");
    space1->set_value("aaa", "1234");
    space1->set_value("aab", 121);
    std::static_pointer_cast<SimpleDevDBSpace>(space1)->serialize("/tmp/aa.test");

    std::shared_ptr<Space> space2 = db->get_space("BBB");
    std::static_pointer_cast<SimpleDevDBSpace>(space2)->deserialize("/tmp/aa.test");
    ASSERT_EQ(boost::get<std::string>(space1->get_value("aaa")), boost::get<std::string>(space2->get_value("aaa")));
    ASSERT_EQ(boost::get<int>(space1->get_value("aab")), boost::get<int>(space2->get_value("aab")));
    ASSERT_NE(boost::get<int>(space1->get_value("aab")), 131);

}

TEST_F(SimpleDevDB_Test, DBSerializeTest) {
    SimpleDevDB *devDb = (SimpleDevDB *) db;
    devDb->wipe(true);
    std::shared_ptr<Space> space1 = db->get_space("AAA");
    space1->set_value("aaa", "1234");
    space1->set_value("aab", 121);
    std::shared_ptr<Space> space2 = db->get_space("AAB");
    space2->set_value("ACC", 133);
    space2->set_value("ADD", "Good Morning");

    devDb->serialize("/tmp");
    devDb->wipe(true);
    //ASSERT_ANY_THROW(space1->get_value("AAA"));

    devDb->deserialize("/tmp");
    space1 = db->get_space("AAA");
    EXPECT_EQ(boost::get<std::string>(space1->get_value("aaa")), "1234");
    EXPECT_EQ(boost::get<int>(space1->get_value("aab")), 121);
    space2 = db->get_space("AAB");
    EXPECT_EQ(boost::get<int>(space2->get_value("ACC")), 133);
    EXPECT_EQ(boost::get<std::string>(space2->get_value("ADD")), "Good Morning");
}


TEST_F(SimpleDevDB_Test, SpaceRedefineKeyValueTest) {

}
