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
    db.dbPtr->remove_all<user_row>();
    db.signup({1,"SchimbaAstaCand","StiSaFolosestiGtest","Visi"}); //inca nu stiu bro
    auto z = db.getUserByUsername("SchimbaAstaCand");
    EXPECT_EQ(db.getUserById(-1),nullptr);
    EXPECT_NE(z, nullptr);
}

TEST(HeloTest,User_creation){
    auto &db = MovieDatabase::instance();
    //This will have to changed at some point when we make dbPtr private.
    db.dbPtr->remove_all<user_row>();
    db.signup({1,"VisiIncaNuStie","SaFoloseascaGtest","Aici"});
    EXPECT_EQ(db.signup({1,"VisiIncaNuStie","SaFoloseascaGtest","Aici"}),nullptr);
    db.signup("MateiAScris","AcestTest");
    EXPECT_EQ(db.signup("MateiAScris","AcestTest"),nullptr);
}

TEST(HeloTest,MovieSearch){
    auto &db = MovieDatabase::instance();
    auto tmp = db.searchMovieTitles("at");
    EXPECT_NE(tmp,nullptr);
}
