//
// Created by perry on 11/11/22.
//

#include "MovieDatabase.h"

std::unique_ptr<movie_row> MovieDatabase::getMovieById(int m_id) const {
    try {
        return (dbPtr->get_pointer<movie_row>(m_id));
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
        return dbPtr->get_pointer<user_row>(u_id);
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
        auto user = std::move(dbPtr->get_all<user_row>(where(c(&user_row::m_username) == username)));
        if (!user.empty())
            return std::make_unique<user_row>(
                    std::move(dbPtr->get_all<user_row>(where(c(&user_row::m_username) == username)).at(0)));
        else {
            return {nullptr};
        }
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<user_row> MovieDatabase::login(const std::string &username, const std::string &password) const {
    try {
        auto usr = dbPtr->get_all<user_row>(
                where(c(&user_row::m_username) == username && c(&user_row::m_password) == password));
        if (usr.empty())
            return {nullptr};
        else
            return std::make_unique<user_row>(std::move(usr.front()));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<user_row> MovieDatabase::signup(const user_row &user) const {
    try {
        auto testval = this->getUserByUsername(user.m_username);
        if (testval == nullptr) {
            return (this->getUserById(dbPtr->insert(user)));
        }
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<user_row>
MovieDatabase::signup(const std::string &username, const std::string &password, const std::string &region) const {
    user_row user(0, username, password, region);
    return this->signup(user);
}

std::unique_ptr<std::vector<watchlist_row>> MovieDatabase::watchlistByUser(int u_id) const {
    try {
        return std::make_unique<std::vector<watchlist_row>>(
                dbPtr->get_all<watchlist_row>(where(c(&watchlist_row::m_user_id) == u_id)));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

/*!
 * TODO: TEST THIS FUNCTION IN GTEST
 * @param u_id
 * @return
 */
std::unique_ptr<std::vector<movie_row>> MovieDatabase::moviesByUserWishlist(int u_id) const {
    try {
        return std::make_unique<std::vector<movie_row>>(std::move(dbPtr->get_all<movie_row>(
                inner_join<watchlist_row>(
                        on(c(&movie_row::m_movie_id) == &watchlist_row::m_movie_id)),
                where(c(&watchlist_row::m_user_id) == u_id))));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

void MovieDatabase::watch(const user_rating_row &entry) const {
    try {
        dbPtr->replace<user_rating_row>(entry);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
}

void MovieDatabase::watch(int user_id, int movie_id, double rating, const std::string &date_modified) const {
    this->watch({user_id, movie_id, rating, date_modified});
}

std::unique_ptr<watchlist_row> MovieDatabase::getWatchEntry(int u_id, int m_id) const {
    try {
        return dbPtr->get_pointer<watchlist_row>(u_id, m_id);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<std::vector<community_tag_row>> MovieDatabase::tagsByUser(int u_id) const {
    try {
        return std::make_unique<std::vector<community_tag_row>>(
                std::move(dbPtr->get_all<community_tag_row>(where(c(&community_tag_row::m_user_id) == u_id))));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

void MovieDatabase::addCommunityTag(const community_tag_row &tagRow) const {
    try {
        dbPtr->remove_all<watchlist_row>(where(c(&community_tag_row::m_tag) == tagRow.m_tag &&
                                               c(&community_tag_row::m_movie_id) == tagRow.m_movie_id) &&
                                         c(&community_tag_row::m_user_id) == tagRow.m_user_id);
        dbPtr->insert(tagRow);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
}

void
MovieDatabase::addCommunityTag(int user_id, int movie_id, const std::string &tag, const std::string &timestamp) const {
    addCommunityTag({user_id, movie_id, tag, timestamp});
}

std::unique_ptr<link_row> MovieDatabase::getLinkEntry(int m_id) const {
    try {
        dbPtr->get_pointer<link_row>(m_id);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<genome_tag_row> MovieDatabase::getTagEntry(int tag_id) const {
    try {
        dbPtr->get_pointer<genome_tag_row>(tag_id);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<genome_scores_row> MovieDatabase::getMovieTagRelevance(int tag_id, int movie_id) const {
    try {
        dbPtr->get_pointer<genome_scores_row>(tag_id, movie_id);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}
