#include <string>
#pragma once

class User
{
	std::string m_username;
	std::string m_password;
	std::string m_region;

public:

	User();
	User(std::string username, std::string password, std::string region);

	std::string GetUsername() const;
	std::string GetPassword() const;
	std::string GetRegion() const;
};