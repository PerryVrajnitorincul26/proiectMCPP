#include "User.h"

User::User(std::string username, std::string password, std::string region)
	:m_username{ username }, m_password{ password }, m_region{ region }
{
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
