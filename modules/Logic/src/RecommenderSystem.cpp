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


//basic recommandation based on liked films
std::vector<std::vector<std::unique_ptr<movie_row>>> RecommenderSystem::recommendedByLikedMovies() {
    auto &dbRef = MovieDatabase::instance();
    std::vector<std::vector<std::unique_ptr<movie_row>>> result;

    for (auto &likedMovie: userLikedMovies) {
        auto movie = dbRef.searchMovieTitles(likedMovie);
        auto genres = movie[0]->m_genres;

        std::vector<std::unique_ptr<movie_row>> recommendedMovies = dbRef.searchMovieGenres(genres);
        result.push_back(std::move(recommendedMovies));
    }

    return result;
}

RecommenderSystem::~RecommenderSystem() {

}

RecommenderSystem::RecommenderSystem() {
    auto &dbref = MovieDatabase::instance();
    tagNames = dbref.getAllTags();
    if (tagNames.empty()) {
        std::cout << "database is likely empty";
        throw -1;
    }

    //We cannot do recommandations on the full dataset unless we somehow optimise the comparison process.
    //Likely through some form of dimensionality reduction like SVD see: https://en.wikipedia.org/wiki/Singular_value_decomposition
    for (int i = 1; i < 100; ++i) {
        //Assumes movie ids 1-100 are valid.
        m_consideredMovies.push_back(std::move(dbref.getMovieTags(i)));
    }
    //Weights will remain 1 until we figure out how to best use them.
    for (const auto &i: tagNames) {
        m_weights.emplace_back(std::make_unique<user_scores_row>(0, i->m_tag_id, 1.0f));
    }
}

RecommenderSystem::RecommenderSystem(int uid) : RecommenderSystem() {
    auto &dbref = MovieDatabase::instance();
    m_uid = uid;
    m_userScores = std::move(dbref.getUserTags(uid));
    if (m_userScores.empty()) {
        std::cout << "User does not have a score entry, Creating one";
        this->populateUserScores();
    }
}

void RecommenderSystem::populateUserScores(int uid) {
    auto &dbref = MovieDatabase::instance();
    if (uid == -1) {
        uid = this->m_uid;
    }
    //this will eventually be replaced by a "create average function"
    for (const auto &i: tagNames) {
        m_userScores.emplace_back(std::make_unique<user_scores_row>(uid, i->m_tag_id, 0.0f));
    }
    auto tmp = dbref.setUserTagRelevance(m_userScores);
    if (tmp.empty()) {
        std::cout << "Something went wrong RecommenderSystem::populateUserScores";
    }
    m_consideredMovies = std::move(dbref.getMovieTagsFromWatchlist(uid));
}

template<typename T>
T
RecommenderSystem::addUserMovieRating(userRatingVec ur, movieRatingVec mr, int index) {
    userRatingVec result = ur;
    result[index]->m_relevance = ur[index]->m_relevance+mr[index]->m_relevance;

    return result;
}

float RecommenderSystem::sumOfGenomes(userRatingVec ur, movieRatingVec mr) {
    float result = 0;

    auto &dbref = MovieDatabase::instance();

    for(int i=0;i<ur.size();i++)
    {
        auto sum = addUserMovieRating<userRatingVec>(ur,mr,i);
        auto relevance = sum[i]->m_relevance;
        result += relevance;
    }


    return result;
}
