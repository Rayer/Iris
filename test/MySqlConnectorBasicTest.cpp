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
    QueryResult result = db->query("select * from al");
    do {
        cout << "Key : " << result->get_column("key") << " value : " << result->get_column("value") << endl;
    }while(result->next());
}

TEST_F(MySqlConnectorBasicTest, ExecuteTest) {
    db->execute("create table if not exists tutorials_tbl (\n"
                "  tutorial_id INT NOT NULL AUTO_INCREMENT,\n"
                "  tutorial_title VARCHAR(100) NOT NULL,\n"
                "  tutorial_author VARCHAR(40) NOT NULL,\n"
                "  PRIMARY KEY (tutorial_id)\n"
                ")\n"
                "");
    db->execute("insert into tutorials_tbl values(null, '1234AA', '1444BB')");
    db->execute("insert into tutorials_tbl values(null, '1134AA', '1444BC')");
    db->execute("insert into tutorials_tbl values(null, '1434AA', '1444BD')");
    db->execute("insert into tutorials_tbl values(null, '1634AA', '1444BE')");
    db->execute("insert into tutorials_tbl values(null, '1834AA', '1444BF')");

    QueryResult result = db->query("select * from tutorials_tbl");

    do {
        cout << "Key : " << result->get_column("tutorial_id") << " value : " << result->get_column("tutorial_title") << endl;
    }while(result->next());
    db->execute("drop table tutorials_tbl");
}
