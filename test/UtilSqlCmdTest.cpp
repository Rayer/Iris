//
// Created by Rayer Tung on 2018/7/19.
//

#include <gtest/gtest.h>
#include "Utils/SqlCmd.h"

using where_clause::Eq;
using where_clause::And;

TEST(SqlQueryTest, BaseQuery) {
    std::string expected = "SELECT c1,c2 FROM table_name;";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").generate();
    EXPECT_EQ(generated, expected);
}

TEST(SqlQueryTest, QueryWithWhere) {
    std::string expected = "SELECT c1,c2 FROM table_name WHERE a='b';";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(
            where_clause::Eq("a", "b")).generate();
    EXPECT_EQ(generated, expected);
}

TEST(SqlQueryTest, QueryWithWhere2) {
    std::string expected = "SELECT c1,c2 FROM table_name WHERE a='b' AND c='d';";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(
            Eq("a", "b") & Eq("c", "d")).generate();
    std::string generated2 = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(
            And(Eq("a", "b"), Eq("c", "d"))).generate();
    EXPECT_EQ(generated, expected);
    EXPECT_EQ(generated2, expected);
}

TEST(SqlQueryTest, QueryWithOrder) {
    std::string expected = "SELECT c1,c2 FROM table_name WHERE a='b' ORDER BY e;";
    std::string generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(Eq("a", "b")).orderBy(
            "e").generate();
    EXPECT_EQ(generated, expected);
    expected = "SELECT c1,c2 FROM table_name WHERE a='b' ORDER BY e DESC;";
    generated = SqlQuery("table_name").addQuery("c1").addQuery("c2").where(Eq("a", "b")).orderBy("e",
                                                                                                 DESCENDING).generate();
    EXPECT_EQ(generated, expected);
}