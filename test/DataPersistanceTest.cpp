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
    DataPersistenceLayer *db = nullptr;


    void SetUp() override {
        db = DataPersistenceManager::getInstance();
        srand((unsigned int) time(nullptr));
    }

    void TearDown() override {
        //std::cout << "TearDown()" << std::endl;
        //Don't delete because it is singleton
        //delete db;
    }

    std::string generateRandomString(int min = 1, int max = 10) {
        static const char *rule = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        size_t rule_length = std::strlen(rule);
        std::string ret;
        int length = rand() % (max - min + 1) + min;
        for (int i = 0; i < length; ++i) ret += rule[rand() % rule_length];
        return ret;
    }


    std::map<std::string, std::shared_ptr<Space>>
    generateTestData(int space_count = 100, int space_size_min = 1, int space_size_max = 10) {
        std::map<std::string, std::shared_ptr<Space>> ret;
        for (int i = 0; i < space_count; i++) {
            //Generate name
            std::string name;
            do {
                name = generateRandomString(1, 16);
                if (ret.find(name) != ret.end()) name = "";
            } while (name.empty());

            std::shared_ptr<Space> space = std::make_shared<SimpleDevDBSpace>();
            int space_size = rand() % (space_size_max - space_size_min) + space_size_min;
            for (int i = 0; i < space_size; ++i) {
                if (rand() % 2)
                    space->set_value(generateRandomString(1, 10), rand());
                else
                    space->set_value(generateRandomString(1, 10), generateRandomString(1, 16));
            }

            ret.insert({name, space});
        }
        return ret;
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


TEST_F(SimpleDevDB_Test, SimpleDevDBPersistTest) {
    SimpleDevDB *simpleDevDB = new SimpleDevDB();
    std::map<std::string, std::shared_ptr<Space>> test_data_raw = generateTestData();

    for (auto const &pair : test_data_raw) {
        auto space = std::static_pointer_cast<SimpleDevDBSpace>(simpleDevDB->get_space(pair.first.c_str()));
        auto keys = std::static_pointer_cast<SimpleDevDBSpace>(pair.second)->get_keys();
        for (const std::string &name : keys) {
            space->set_value(name.c_str(), pair.second->get_value(name.c_str()));
        }
    }

    std::string folder = "/tmp/" + generateRandomString(5, 6);

    boost::filesystem::remove(folder);
    simpleDevDB->serialize(folder);

    delete simpleDevDB;

    simpleDevDB = new SimpleDevDB();
    simpleDevDB->deserialize(folder);


}
