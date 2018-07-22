//
// Created by Rayer on 20/06/2018.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Data/DataPersistenceManager.h>
#include <Data/SqlKVDatabase.h>
#include <Logger/MasterLogger.h>

using namespace Iris;

class SqlKVDatabase_Test : public ::testing::Test {

protected:
    KVDataPersistenceLayer *db = nullptr;
    //This map stores all record that DB operates, used to verdict correct answer.
    typedef std::map<std::string, KVSpace::ValueType> SpaceSpec;
    typedef std::map<std::string, SpaceSpec> DBSpec;
    DBSpec cache; //This cache is used in stress test case
    MasterLogger *logger;

    SqlKVDatabase_Test() {
        db = new SqlKVDatabase("localhost", "iris", "iris", "iris_test");
        srand((unsigned int) time(nullptr));
        db->wipe(true);
        logger = MasterLogger::getLogger();
    }

    void SetUp() override {

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

    void generateStressTestData(KVDataPersistenceLayer* dpl, int space_count = 100, int space_size_min = 1, int space_size_max = 10) {

        cache.clear();

        std::map<std::string, std::shared_ptr<KVSpace> > spaceList;
        for(int i = 0; i < space_count; ++i) {
            std::string space_name = generateRandomString(1, 16);
            spaceList.insert(std::make_pair(space_name, dpl->get_space(space_name)));
            //cache[space_name] = SpaceSpec{};
            logger->trace("Get space : " + space_name);

            for(std::pair<std::string, std::shared_ptr<KVSpace> > pair : spaceList) {
                int space_size = rand() % (space_size_max - space_size_min) + space_size_min;
                for(int j = 0; j < space_size; ++j) {
                    std::string column_name = generateRandomString(1, 10);
                    KVSpace::ValueType value = (rand() % 2) ? (KVSpace::ValueType)rand() : (KVSpace::ValueType)generateRandomString(1, 16);
                    cache[pair.first].insert(std::make_pair(column_name, value));
                    pair.second->set_value(column_name, value);
                }

            }

        }
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

TEST_F(SqlKVDatabase_Test, StressTest) {
    generateStressTestData(db);
}
