#include "RecommenderSystem.h"

std::vector<std::string> RecommenderSystem::GetUserLikedGenres() const
{
	return userLikedGenres;
}

std::vector<std::string> RecommenderSystem::GetUserLikedMovies() const
{
	return userLikedMovies;
}
