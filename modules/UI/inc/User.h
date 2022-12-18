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

    User(const std::string &username, const std::string &region);

	std::string getUsername() const;

    bool operator==(const User &rhs) const;

    bool operator!=(const User &rhs) const;

    std::string getPassword() const;

    void setMUsername(const std::string &mUsername);

    void setMPassword(const std::string &mPassword);

    void setMRegion(const std::string &mRegion);

    void setMLikedGenres(const std::vector<std::string> &mLikedGenres);

    std::string getRegion() const;
	std::vector<std::string> getLikedGenres() const;

	~User();
};