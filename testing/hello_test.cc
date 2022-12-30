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
TEST(HeloTest, GetUserLikedGenres) {
    RecommenderSystem *recommender = new RecommenderSystem(1);
    std::vector<std::string> expectedLikedGenres = {"Action", "Comedy", "Drama"};
    recommender->setUserLikedGenres(expectedLikedGenres);

    std::vector<std::string> actualLikedGenres = recommender->GetUserLikedGenres();

    ASSERT_EQ(expectedLikedGenres, actualLikedGenres);
}

//Test that the setUserLikedMovies method correctly updates the user's list of liked movies.
TEST(HeloTest, TestSetUserLikedGenres) {
    RecommenderSystem *rs = new RecommenderSystem(1);
    std::vector<std::string> likedGenres = {"action", "comedy", "drama"};
    rs->setUserLikedGenres(likedGenres);
    std::vector<std::string> result = rs->GetUserLikedGenres();
    EXPECT_EQ(result, likedGenres);
}

// Test that the MovieDatabase singleton can be correctly instantiated using the instance() method
TEST(HeloTest, TestSingletonInstantiation) {
    MovieDatabase& db1 = MovieDatabase::instance();
    MovieDatabase& db2 = MovieDatabase::instance();
    EXPECT_EQ(&db1, &db2);
}

// Test that the getMovieById function correctly retrieves a movie from the database by its ID
TEST(HeloTest, TestGetMovieById) {
    MovieDatabase& db = MovieDatabase::instance();
    std::unique_ptr<movie_row> movie = db.getMovieById(1);
    EXPECT_EQ(movie->m_movie_id, 1);
    EXPECT_STREQ(movie->m_title.c_str(), "The Shawshank Redemption");
    EXPECT_STREQ(movie->m_genres.c_str(), "Drama");
}

// Test that the searchMovieTitles function correctly retrieves a list of movies from the database whose titles contain a specified search string
TEST(HeloTest, TestSearchMovieTitles) {
    MovieDatabase& db = MovieDatabase::instance();
    std::vector<std::unique_ptr<movie_row>> movies = db.searchMovieTitles("The");
    EXPECT_EQ(movies.size(), 1);
    EXPECT_EQ(movies[0]->m_movie_id, 1);
    EXPECT_STREQ(movies[0]->m_title.c_str(), "The Shawshank Redemption");
    EXPECT_STREQ(movies[0]->m_genres.c_str(), "Drama");
}

// Test that the searchMovieGenres function correctly retrieves a list of movies from the database that belong to a specified genre
TEST(HeloTest, TestSearchMovieGenres) {
    MovieDatabase& db = MovieDatabase::instance();
    std::vector<std::unique_ptr<movie_row>> movies = db.searchMovieGenres("Drama");
    EXPECT_EQ(movies.size(), 1);
    EXPECT_EQ(movies[0]->m_movie_id, 1);
    EXPECT_STREQ(movies[0]->m_title.c_str(), "The Shawshank Redemption");
    EXPECT_STREQ(movies[0]->m_genres.c_str(), "Drama");
}

// Test that the getUserById function correctly retrieves a user from the database by their ID
TEST(HeloTest, TestGetUserById) {
    MovieDatabase& db = MovieDatabase::instance();
    std::unique_ptr<user_row> user = db.getUserById(1);
    EXPECT_EQ(user->m_user_id, 1);
    EXPECT_STREQ(user->m_username.c_str(), "perry");
    EXPECT_STREQ(user->m_password.c_str(), "password");
}

// Test that the getUserByUsername function correctly retrieves a user from the database by their username.
TEST(HeloTest, TestGetUserByUsername) {
    auto& db = MovieDatabase::instance();
    auto user = db.getUserByUsername("user1");
    EXPECT_EQ(user->m_user_id, 1);
    EXPECT_EQ(user->m_username, "user1");
    EXPECT_EQ(user->m_password, "password1");
}

// Test that the populateUserScores function correctly populates the m_userScores list with scores for each tag.
TEST(HeloTest, TestPopulateUserScores) {
    RecommenderSystem *rs = new RecommenderSystem(1);
    rs->populateUserScores(1);
    EXPECT_EQ(rs->m_userScores.size(), 2);
    EXPECT_EQ(rs->m_userScores[0]->m_relevance, 3.5);
    EXPECT_EQ(rs->m_userScores[1]->m_relevance, 2.5);
}

//Test that setUserLikedGenres correctly updates the user's liked genres.
TEST(HeloTest, SetUserLikedGenres) {
    RecommenderSystem *rs = new RecommenderSystem(1);
    std::vector<std::string> expectedLikedGenres = {"Action", "Drama", "Comedy"};
    rs->setUserLikedGenres(expectedLikedGenres);
    std::vector<std::string> actualLikedGenres = rs->GetUserLikedGenres();
    EXPECT_EQ(expectedLikedGenres, actualLikedGenres);

    std::vector<std::string> newExpectedLikedGenres = {"Thriller", "Sci-Fi", "Adventure"};
    rs->setUserLikedGenres(newExpectedLikedGenres);
    actualLikedGenres = rs->GetUserLikedGenres();
    EXPECT_EQ(newExpectedLikedGenres, actualLikedGenres);
}


