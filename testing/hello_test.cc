//
// Created by Perry on 11/7/2022.
//
#include <gtest/gtest.h>
#include <db_headers.h>
#include <MovieDatabase.h>
#include <RecommenderSystem.h>

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
    // Expect two strings not to be equal.
    EXPECT_STRNE("hello", "world");
    // Expect equality.
    EXPECT_EQ(7 * 6, 42);
}

TEST(HeloTest, db_get_user) {
    auto &db = MovieDatabase::instance();
    db.dbPtr->remove_all<user_row>();
    db.signup({1, "SchimbaAstaCand", "StiSaFolosestiGtest", "Visi"}); //inca nu stiu bro
    auto z = db.getUserByUsername("SchimbaAstaCand");
    EXPECT_EQ(db.getUserById(-1), nullptr);
    EXPECT_NE(z, nullptr);
}

TEST(HeloTest, User_creation) {
    auto &db = MovieDatabase::instance();
    //This will have to changed at some point when we make dbPtr private.
    db.dbPtr->remove_all<user_row>();
    db.signup({1, "VisiIncaNuStie", "SaFoloseascaGtest", "Aici"});
    EXPECT_EQ(db.signup({1, "VisiIncaNuStie", "SaFoloseascaGtest", "Aici"}), nullptr);
    db.signup("MateiAScris", "AcestTest");
    EXPECT_EQ(db.signup("MateiAScris", "AcestTest"), nullptr);
}

TEST(HeloTest, MovieSearch) {
    auto &db = MovieDatabase::instance();
    auto tmp = db.searchMovieTitles("at");
    EXPECT_FALSE(tmp.empty());
}

TEST(HeloTest, another_test) {
    EXPECT_ANY_THROW(new RecommenderSystem(-1));
}

TEST(HeloTest, servus_test) {
    auto &db = MovieDatabase::instance();
    db.signup({-1, "TestUser", "IsATest", "Romania"});
    EXPECT_NO_THROW(new RecommenderSystem(-1));
}

//verifies if there are at least 100 movies that respect the condition
TEST(HeloTest, ConstructorTest) {
    RecommenderSystem *rs = new RecommenderSystem(1);
    EXPECT_GE(rs->m_consideredMovies.size(), 100);
}

TEST(HeloTest, RecommendedByLikedMoviesTest) {
    RecommenderSystem *rs = new RecommenderSystem(1);
    std::vector<std::string> likedMovies = {"Movie A", "Movie B", "Movie C"};
    rs->setUserLikedMovies(likedMovies);
    auto result = rs->recommendedByLikedMovies();
    EXPECT_GE(result.size(), 1);
}

//Test the GetUserLikedGenres function to ensure that it correctly returns the genres that the user has specified they like.
TEST(HeloTest, TestGetUserLikedGenres) {
    RecommenderSystem *rs = new RecommenderSystem(1);
    rs->setUserLikedGenres({"Action", "Adventure", "Comedy"});
    EXPECT_EQ(rs->GetUserLikedGenres(), std::vector<std::string>{"Action", "Adventure", "Comedy"});
}

//Test the GetUserLikedMovies function to ensure that it correctly returns the movies that the user has specified they like.
TEST(HeloTest, TestGetUserLikedMovies) {
    RecommenderSystem *rs = new RecommenderSystem(1);
    rs->setUserLikedMovies({"The Shawshank Redemption", "The Godfather", "The Godfather: Part II"});
    EXPECT_EQ(rs->GetUserLikedMovies(), std::vector<std::string>{"The Shawshank Redemption", "The Godfather", "The Godfather: Part II"});
}