#include <vector>
#include <string>
#include <db_headers.h>
#include <MovieDatabase.h>

//If I'm correct user vector should be the same.
using movieVec = decltype(std::vector<genome_scores_row>());

class RecommenderSystem {
    std::vector<std::string> userLikedGenres;
    std::vector<std::string> userLikedMovies;

public:
    RecommenderSystem(const std::vector<std::string> &userLikedGenres, const std::vector<std::string> &userLikedMovies);

    RecommenderSystem();

    std::vector<std::string> GetUserLikedGenres() const;

    std::vector<std::string> GetUserLikedMovies() const;

    void setUserLikedGenres(const std::vector<std::string> &userLikedGenres);

    void setUserLikedMovies(const std::vector<std::string> &userLikedMovies);

    std::vector<std::unique_ptr<movie_row>> recommendedByLikedGenres(std::string genre);

    std::vector<std::vector<std::unique_ptr<movie_row>>> recommendedByLikedMovies();

    virtual ~RecommenderSystem();
};