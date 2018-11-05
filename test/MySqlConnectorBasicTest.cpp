//
// Created by CORP\rayer on 10/31/18.
//

#include <gtest/gtest.h>
#include <Data/DBEngine/MySqlProvider.h>
#include <iostream>
using namespace Iris;
using namespace std;

class MySqlConnectorBasicTest : public ::testing::Test {

protected:
    IDBEngineProvider* db;
    virtual void SetUp() {
        db = new MySqlProvider();
        db->connect("node.rayer.idv.tw", "iris", "iris", "iris_test");
    }

    virtual void TearDown() {
        db->cleanup();
    }

};

TEST_F(MySqlConnectorBasicTest, QueryTest) {
    QueryResult result = db->query("select * from XS");
    for(int i = 0; i < result->row_count(); ++i) {
        cout << "Key : " << result->get_column("key") << " value : " << result->get_column("value") << endl;
    }
}
