#include <vector>
#include <string>

class RecommenderSystem
{
	std::vector<std::string> userLikedGenres;
	std::vector<std::string> userLikedMovies;

public:

	std::vector<std::string> GetUserLikedGenres() const;
	std::vector<std::string> GetUserLikedMovies() const;
};