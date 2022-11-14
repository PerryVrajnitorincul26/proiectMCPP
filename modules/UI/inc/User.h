#include <string>
#include <vector>
#pragma once

class User
{
	std::string m_username;
	std::string m_password;
	std::string m_region;
	std::vector<std::string> m_likedGenres;

public:

	User();
	User(const std::string &username, const std::string &password, const std::string &region);

	std::string GetUsername() const;
	std::string GetPassword() const;
	std::string GetRegion() const;
	std::vector<std::string> GetLikedGenres() const;

	~User();
};