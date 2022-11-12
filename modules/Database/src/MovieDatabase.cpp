//
// Created by perry on 11/11/22.
//

#include "MovieDatabase.h"

std::unique_ptr<movie_row> MovieDatabase::getMovieById(int m_id) const {
    try {
        return std::make_unique<movie_row>(std::move(dbPtr->get<movie_row>(m_id)));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<std::vector<movie_row>> MovieDatabase::searchMovieTitles(const std::string &src) const {
    ///I think this shouldn't involve copying anything but i may be wrong
    try {
        return std::make_unique<std::vector<movie_row>>(std::move(
                dbPtr->get_all<movie_row>(where(like(&movie_row::m_title, "%" + src + "%")))));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<user_row> MovieDatabase::getUserById(int u_id) const {
    try {
        return std::make_unique<user_row>(std::move(dbPtr->get<user_row>(u_id)));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<std::vector<user_row>> MovieDatabase::searchUsersByUsername(const std::string &src) const {
    try {
        return std::make_unique<std::vector<user_row>>(std::move(
                dbPtr->get_all<user_row>(where(like(&user_row::m_username, "%" + src + "%")))));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<std::vector<user_rating_row>> MovieDatabase::getUserReviews(int u_id) const {
    try {
        return std::make_unique<std::vector<user_rating_row>>(std::move(
                dbPtr->get_all<user_rating_row>(where(c(&user_rating_row::m_user_id) == u_id))));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

/*!
 * This should return first user with matching username, which SHOULD be the only user with such a name as there is
 * a constraint on that field
 * @param username
 * @return unique_ptr to on
 */
std::unique_ptr<user_row> MovieDatabase::getUserByUsername(const std::string &username) const {
    try {
        return std::make_unique<user_row>(
                std::move(dbPtr->get_all<user_row>(where(c(&user_row::m_username) == username))[0]));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

bool MovieDatabase::login(const std::string &username, const std::string &password) const {
    try {
        auto usr = dbPtr->get_all<user_row>(
                where(c(&user_row::m_username) == username && c(&user_row::m_password) == password));
        if (usr.empty())
            return false;
        else
            return true;
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return false;
}
