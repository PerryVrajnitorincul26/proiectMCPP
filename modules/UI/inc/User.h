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

    bool operator==(const User &rhs) const;

    bool operator!=(const User &rhs) const;

    std::string GetPassword() const;

    void setMUsername(const std::string &mUsername);

    void setMPassword(const std::string &mPassword);

    void setMRegion(const std::string &mRegion);

    void setMLikedGenres(const std::vector<std::string> &mLikedGenres);

    std::string GetRegion() const;
	std::vector<std::string> GetLikedGenres() const;

	~User();
};