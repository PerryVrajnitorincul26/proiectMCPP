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

User::~User() {}

void User::setMUsername(const std::string &mUsername) {
    m_username = mUsername;
}

void User::setMPassword(const std::string &mPassword) {
    m_password = mPassword;
}

void User::setMRegion(const std::string &mRegion) {
    m_region = mRegion;
}

void User::setMLikedGenres(const std::vector<std::string> &mLikedGenres) {
    m_likedGenres = mLikedGenres;
}

bool User::operator==(const User &rhs) const {
    return m_username == rhs.m_username &&
           m_password == rhs.m_password &&
           m_region == rhs.m_region &&
           m_likedGenres == rhs.m_likedGenres;
}

bool User::operator!=(const User &rhs) const {
    return !(rhs == *this);
};
