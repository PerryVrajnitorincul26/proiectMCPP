//
// Created by Perry on 11/7/2022.
//
#include <gtest/gtest.h>
#include <db_headers.h>
#include <MovieDatabase.h>
// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(HeloTest,db_get_user){
    auto &db = MovieDatabase::instance();
    auto z = db.getUserById(1);
    EXPECT_EQ(db.getUserById(-1),nullptr);
    EXPECT_NE(z, nullptr);
}
