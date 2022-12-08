#include <vector>
#include <string>
#include <db_headers.h>
#include <MovieDatabase.h>
//If I'm correct user vector should be the same.
using movieRatingVec = decltype(std::vector<std::unique_ptr<genome_scores_row>>());
using userRatingVec = decltype(std::vector<std::unique_ptr<user_scores_row>>());
using tagNameVec = decltype(std::vector<std::unique_ptr<genome_tag_row>>());

class RecommenderSystem {
    int m_uid;
    userRatingVec m_userScores, m_weights;
    tagNameVec tagNames;
    std::vector<movieRatingVec> m_consideredMovies;
    std::vector<std::string> userLikedMovies, userLikedGenres;

public:
    RecommenderSystem(const std::vector<std::string> &userLikedGenres, const std::vector<std::string> &userLikedMovies);

    RecommenderSystem();

    RecommenderSystem(int uid);

    void populateUserScores(int uid = -1);

    std::vector<std::string> GetUserLikedGenres() const;

    std::vector<std::string> GetUserLikedMovies() const;

    void setUserLikedGenres(const std::vector<std::string> &userLikedGenres);

    void setUserLikedMovies(const std::vector<std::string> &userLikedMovies);

    std::vector<std::unique_ptr<movie_row>> recommendedByLikedGenres(std::string genre);

    std::vector<std::vector<std::unique_ptr<movie_row>>> recommendedByLikedMovies();

    virtual ~RecommenderSystem();
};