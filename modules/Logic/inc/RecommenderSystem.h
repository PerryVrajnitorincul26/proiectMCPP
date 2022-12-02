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

    std::vector<std::string> GetUserLikedGenres() const;

    std::vector<std::string> GetUserLikedMovies() const;
};