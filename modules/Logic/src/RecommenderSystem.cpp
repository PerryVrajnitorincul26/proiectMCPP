#include "RecommenderSystem.h"

std::vector<std::string> RecommenderSystem::GetUserLikedGenres() const {
    return userLikedGenres;
}

std::vector<std::string> RecommenderSystem::GetUserLikedMovies() const {
    return userLikedMovies;
}

std::unique_ptr<std::vector<movie_row>> RecommenderSystem::recommendedByGenres(std::string genre) {
    auto &dbRef = MovieDatabase::instance();

    std::unique_ptr<std::vector<movie_row>> searchResult;
    searchResult = dbRef.searchMovieGenres(genre);

    return searchResult;
}

void RecommenderSystem::setUserLikedGenres(const std::vector<std::string> &userLikedGenres) {
    RecommenderSystem::userLikedGenres = userLikedGenres;
}

void RecommenderSystem::setUserLikedMovies(const std::vector<std::string> &userLikedMovies) {
    RecommenderSystem::userLikedMovies = userLikedMovies;
}

RecommenderSystem::RecommenderSystem(const std::vector<std::string> &userLikedGenres,
                                     const std::vector<std::string> &userLikedMovies) : userLikedGenres(
        userLikedGenres), userLikedMovies(userLikedMovies) {}

RecommenderSystem::RecommenderSystem() {}
