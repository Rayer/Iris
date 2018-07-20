//
// Created by Rayer Tung on 2018/7/19.
//

#include <gtest/gtest.h>
#include "Utils/SqlCmd.h"

using where_clause::Eq;
using where_clause::And;
using where_clause::Not;

TEST(SqlCmdTest, BaseQuery) {
    std::string expected = "SELECT c1,c2 FROM table_name;";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").generate();
    EXPECT_EQ(generated, expected);
}

TEST(SqlCmdTest, BaseWhere) {
    std::string expected = "SELECT c1,c2 FROM table_name WHERE a='b';";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(
            where_clause::Eq("a", "b")).generate();
    EXPECT_EQ(generated, expected);
}

TEST(SqlCmdTest, BaseWhere2) {
    std::string expected = "SELECT c1,c2 FROM table_name WHERE a='b' AND c='2' AND d='2.55';";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(
            Eq("a", "b") & Eq("c", 2) & Eq("d", 2.55)).generate();
    std::string generated2 = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(
            And(And(Eq("a", "b"), Eq("c", 2)), Eq("d", 2.55))).generate();
    EXPECT_EQ(generated, expected);
    EXPECT_EQ(generated2, expected);
}

TEST(SqlCmdTest, WhereWithNull) {
    std::string expected = "SELECT c1,c2 FROM table_name WHERE c3 is null;";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(Eq("c3", "")).generate();
    EXPECT_EQ(generated, expected);
}

TEST(SqlCmdTest, WhereWithNot) {
    std::string expected = "SELECT c1,c2 FROM table_name WHERE c3<>'c4';";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(Not("c3", "c4")).generate();
    EXPECT_EQ(generated, expected);
}

TEST(SqlCmdTest, WhereWithNotNull) {
    std::string expected = "SELECT c1,c2 FROM table_name WHERE c3 is not null;";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(Not("c3", "")).generate();
    EXPECT_EQ(generated, expected);
}

TEST(SqlCmdTest, QueryWithOrder) {
    std::string expected = "SELECT c1,c2 FROM table_name WHERE a='b' ORDER BY e;";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(Eq("a", "b")).orderBy(
            "e").generate();
    EXPECT_EQ(generated, expected);
    expected = "SELECT c1,c2 FROM table_name WHERE a='b' ORDER BY e DESC;";
    generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(Eq("a", "b"))
            .orderBy("e", DESCENDING).generate();
    EXPECT_EQ(generated, expected);
}

TEST(SqlCmdTest, BaseUpdate) {
    std::string expected = "UPDATE table_name SET c1='v1',c2='2',c3='3.5' WHERE c4='v4';";
    std::string generated = SqlUpdate("table_name").setValue("c1", "v1").setValue("c2", 2).setValue("c3", 3.5)
            .where(Eq("c4", "v4")).generate();
    EXPECT_EQ(generated, expected);
}

TEST(SqlCmdTest, BaseInsert) {
    std::string expected = "INSERT INTO table_name (c1,c2,c3,c4) VALUES ('v1','v2','3','2.7');";
    std::string generated = SqlInsert("table_name").insertValue("c1", "v1").insertValue("c2", "v2")
            .insertValue("c3", 3).insertValue("c4", 2.7).generate();
    EXPECT_EQ(generated, expected);
}