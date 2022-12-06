#include "RecommenderSystem.h"

std::vector<std::string> RecommenderSystem::GetUserLikedGenres() const {
    return userLikedGenres;
}

std::vector<std::string> RecommenderSystem::GetUserLikedMovies() const {
    return userLikedMovies;
}

std::vector<std::unique_ptr<movie_row>> RecommenderSystem::recommendedByLikedGenres(std::string genre) {
    auto &dbRef = MovieDatabase::instance();

    auto searchResult = dbRef.searchMovieGenres(genre);

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

//basic recommandation based on liked films
std::vector<std::unique_ptr<std::vector<movie_row>>> RecommenderSystem::recommendedByLikedMovies() {
    auto &dbRef = MovieDatabase::instance();
    std::vector<std::unique_ptr<std::vector<movie_row>>> result;

    for(auto &likedMovie: userLikedMovies)
    {
        auto movie = *dbRef.searchMovieTitles(likedMovie);
        auto genres = movie[0].m_genres;

        auto recommendedMovies = dbRef.searchMovieGenres(genres);
        result.push_back(std::move(recommendedMovies));
    }

    return result;
}

RecommenderSystem::~RecommenderSystem() {

}