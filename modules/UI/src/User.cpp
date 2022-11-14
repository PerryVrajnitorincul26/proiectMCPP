#include "../inc/User.h"
#include <sstream>

User::User(const std::string &username, const std::string &password, const std::string &region)
{
	if (username.empty())
		throw std::invalid_argument("Username cannot be empty");

	if (password.empty())
		throw std::invalid_argument("Password cannot be empty");

	if (region.empty())
		throw std::invalid_argument("Region cannot be empty");

	this->m_username = username;
	this->m_password = password;
	this->m_region = region;
}

std::string User::GetUsername() const
{
	return m_username;
}

std::string User::GetPassword() const
{
	return m_password;
}

std::string User::GetRegion() const
{
	return m_region;
}

std::vector<std::string> User::GetLikedGenres() const
{
	return m_likedGenres;
}

User::~User() {};
