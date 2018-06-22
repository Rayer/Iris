//
// Created by Rayer on 20/06/2018.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Data/SimpleKVDevDB.h>
#include <Data/DataPersistenceManager.h>
#include <Data/SqlKVDatabase.h>

using namespace Iris;

class SqlKVDatabase_Test : public ::testing::Test {

protected:
    KVDataPersistenceLayer *db = nullptr;


    void SetUp() override {
        db = new SqlKVDatabase("localhost", "iris", "iris", "iris_test");
        srand((unsigned int) time(nullptr));
        db->wipe(true);
    }

    void TearDown() override {
        //std::cout << "TearDown()" << std::endl;
        //Don't delete because it is singleton
        //delete db;
    }

    std::string generateRandomString(int min = 1, int max = 10) {
        static const char *rule = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        size_t rule_length = std::strlen(rule);
        std::string ret;
        int length = rand() % (max - min + 1) + min;
        for (int i = 0; i < length; ++i) ret += rule[rand() % rule_length];
        return ret;
    }


    std::map<std::string, std::shared_ptr<KVSpace>>
    generateTestData(int space_count = 100, int space_size_min = 1, int space_size_max = 10) {
        std::map<std::string, std::shared_ptr<KVSpace>> ret;
        for (int i = 0; i < space_count; i++) {
            //Generate name
            std::string name;
            do {
                name = generateRandomString(1, 16);
                if (ret.find(name) != ret.end()) name = "";
            } while (name.empty());

            std::shared_ptr<KVSpace> space = std::make_shared<SimpleKVDevDBSpace>();
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


TEST_F(SqlKVDatabase_Test, SpaceAccessTest) {
    std::string SPACE_NAME = generateRandomString(4, 6);
    std::string KEY1 = generateRandomString(1, 10);
    std::string KEY2 = generateRandomString(1, 10);
    std::string STR_VALUE = generateRandomString(5, 20);
    int INT_VALUE = rand();
    std::shared_ptr<KVSpace> space = db->get_space(SPACE_NAME);
    space->set_value(KEY1, STR_VALUE);
    EXPECT_EQ(boost::get<std::string>(space->get_value(KEY1)), STR_VALUE);
    space->set_value(KEY2, INT_VALUE);
    EXPECT_EQ(boost::get<int>(space->get_value(KEY2)), INT_VALUE);
}

TEST_F(SqlKVDatabase_Test, SpaceAccessReferenceTest) {
    std::string space_name = generateRandomString();
    std::shared_ptr<KVSpace> space = db->get_space(space_name);
    std::string key = generateRandomString();
    std::string str_value = generateRandomString();
    space->set_value(key, str_value);
    std::shared_ptr<KVSpace> space2 = db->get_space(space_name);
    EXPECT_EQ(boost::get<std::string>(space2->get_value(key)), str_value);
}

TEST_F(SqlKVDatabase_Test, SpaceGetNilValueTest) {
    std::string space_name = generateRandomString();
    std::string key = generateRandomString();
    std::shared_ptr<KVSpace> space = db->get_space(space_name);
    EXPECT_ANY_THROW(space->get_value(key));
}

//
//TEST_F(SqlKVDatabase_Test, SpaceSerializeTest) {
//    std::string space_name = generateRandomString();
//    std::shared_ptr<KVSpace> space1 = db->get_space(space_name);
//    std::string key1 = generateRandomString();
//    std::string value1 = generateRandomString();
//    std::string key2 = generateRandomString();
//    int value2 = rand();
//    space1->set_value(key1, value1);
//    space1->set_value(key2, value2);
//    std::static_pointer_cast<SimpleKVDevDBSpace>(space1)->serialize("/tmp/" + space_name + ".test");
//
//    std::shared_ptr<KVSpace> space2 = db->get_space(generateRandomString());
//    std::static_pointer_cast<SimpleKVDevDBSpace>(space2)->deserialize("/tmp/" + space_name + ".test");
//    EXPECT_EQ(boost::get<std::string>(space1->get_value(key1)), boost::get<std::string>(space2->get_value(key1)));
//    EXPECT_EQ(boost::get<int>(space1->get_value(key2)), boost::get<int>(space2->get_value(key2)));
//    EXPECT_EQ(boost::get<int>(space1->get_value(key2)), value2);
//
//}
//
//TEST_F(SqlKVDatabase_Test, DBSerializeTest) {
//    SimpleKVDevDB *devDb = (SimpleKVDevDB *) db;
//    devDb->wipe(true);
//    std::string space_name1 = generateRandomString();
//    std::string key1 = generateRandomString();
//    std::string key2 = generateRandomString();
//    std::string value1 = generateRandomString();
//    int value2 = rand();
//    std::shared_ptr<KVSpace> space1 = db->get_space(space_name1);
//    space1->set_value(key1, value1);
//    space1->set_value(key2, value2);
//    std::string space_name2 = generateRandomString();
//    std::shared_ptr<KVSpace> space2 = db->get_space(space_name2);
//    std::string key3 = generateRandomString();
//    std::string key4 = generateRandomString();
//    std::string value3 = generateRandomString();
//    int value4 = rand();
//    space2->set_value(key3, value3);
//    space2->set_value(key4, value4);
//
//    devDb->serialize("/tmp");
//    devDb->wipe(true);
//    ASSERT_ANY_THROW(space1->get_value("AAA"));
//
//    devDb->deserialize("/tmp");
//    space1 = db->get_space(space_name1);
//    EXPECT_EQ(boost::get<std::string>(space1->get_value(key1)), value1);
//    EXPECT_EQ(boost::get<int>(space1->get_value(key2)), value2);
//    space2 = db->get_space(space_name2);
//    EXPECT_EQ(boost::get<std::string>(space2->get_value(key3)), value3);
//    EXPECT_EQ(boost::get<int>(space2->get_value(key4)), value4);
//}

//
//TEST_F(SqlKVDatabase_Test, SimpleDevDBPersistTest) {
//    SimpleKVDevDB *simpleDevDB = new SimpleKVDevDB();
//    std::map<std::string, std::shared_ptr<KVSpace>> test_data_raw = generateTestData();
//
//    for (auto const &pair : test_data_raw) {
//        auto space = std::static_pointer_cast<SimpleKVDevDBSpace>(simpleDevDB->get_space(pair.first));
//        auto keys = std::static_pointer_cast<SimpleKVDevDBSpace>(pair.second)->get_keys();
//        for (const std::string &name : keys) {
//            space->set_value(name, pair.second->get_value(name));
//        }
//    }
//
//    //std::string folder = "/tmp/" + generateRandomString(5, 6);
//    std::string folder = boost::filesystem::complete(boost::filesystem::temp_directory_path()).generic_string() +
//                         generateRandomString(5, 6);
//
//    boost::filesystem::remove(folder);
//    simpleDevDB->serialize(folder);
//
//    delete simpleDevDB;
//
//    simpleDevDB = new SimpleKVDevDB();
//    simpleDevDB->deserialize(folder);
//
//
//}
