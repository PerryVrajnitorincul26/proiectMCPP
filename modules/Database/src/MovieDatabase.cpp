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

std::vector<std::unique_ptr<movie_row>> MovieDatabase::searchMovieTitles(const std::string &src) const {
    ///I think this shouldn't involve copying anything but i may be wrong
    try {
        return dbPtr->get_all_pointer<movie_row>(where(like(&movie_row::m_title, "%" + src + "%")));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {};
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
std::vector<std::unique_ptr<movie_row>> MovieDatabase::moviesRatedByUser(int u_id) const {
    try {
        return dbPtr->get_all_pointer<movie_row>(
                inner_join<user_rating_row>(
                        on(c(&movie_row::m_movie_id) == &user_rating_row::m_movie_id)),
                where(c(&user_rating_row::m_user_id) == u_id));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {};
}

std::unique_ptr<user_rating_row> MovieDatabase::watch(const user_rating_row &entry) const {
    try {
        dbPtr->replace<user_rating_row>(entry);
        return dbPtr->get_pointer<user_rating_row>(entry.m_user_id, entry.m_movie_id);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<user_rating_row>
MovieDatabase::watch(int user_id, int movie_id, double rating, const std::string &date_modified) const {
    return this->watch({user_id, movie_id, rating, date_modified});
}


std::unique_ptr<user_rating_row> MovieDatabase::getWatchEntry(int u_id, int m_id) const {
    try {
        return dbPtr->get_pointer<user_rating_row>(u_id, m_id);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::vector<std::unique_ptr<community_tag_row>> MovieDatabase::tagsByUser(int u_id) const {
    try {
        return dbPtr->get_all_pointer<community_tag_row>(where(c(&community_tag_row::m_user_id) == u_id));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {};
}

std::unique_ptr<community_tag_row> MovieDatabase::addCommunityTag(const community_tag_row &tagRow) const {
    try {
        dbPtr->remove_all<community_tag_row>(where(c(&community_tag_row::m_tag) == tagRow.m_tag &&
                                                   c(&community_tag_row::m_movie_id) == tagRow.m_movie_id) &&
                                             c(&community_tag_row::m_user_id) == tagRow.m_user_id);
        auto temp = dbPtr->insert(tagRow);
        return dbPtr->get_pointer<community_tag_row>(temp);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<community_tag_row>
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

std::unique_ptr<genome_tag_row> MovieDatabase::getTagName(int tag_id) const {
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

std::vector<std::unique_ptr<movie_row>> MovieDatabase::searchMovieGenres(const std::string &src) const {
    try {
        return dbPtr->get_all_pointer<movie_row>(where(like(&movie_row::m_genres, "%" + src + "%")));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {};
}

std::unique_ptr<user_scores_row> MovieDatabase::getUserTagRelevance(int tag_id, int user_id) const {
    try {
        return dbPtr->get_pointer<user_scores_row>(tag_id, user_id);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::vector<std::unique_ptr<genome_scores_row>> MovieDatabase::getMovieTags(int movie_id) const {
    try {
        return dbPtr->get_all_pointer<genome_scores_row>(where(c(&genome_scores_row::m_movie_id) == movie_id));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {};
}

std::vector<std::unique_ptr<user_scores_row>> MovieDatabase::getUserTags(int user_id) const {
    try {
        return dbPtr->get_all_pointer<user_scores_row>(where(c(&user_scores_row::m_user_id) == user_id));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {};
}

std::unique_ptr<genome_scores_row> MovieDatabase::setMovieTagRelevance(const genome_scores_row &rhs) {
    try {
        dbPtr->replace<genome_scores_row>(rhs);
        return dbPtr->get_pointer<genome_scores_row>(rhs.m_movie_id, rhs.m_tag_id);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<user_scores_row>
MovieDatabase::setUserTagRelevance(const user_scores_row &rhs) {
    try {
        dbPtr->replace<user_scores_row>(rhs);
        return dbPtr->get_pointer<user_scores_row>(rhs.m_user_id, rhs.m_tag_id);
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {nullptr};
}

std::unique_ptr<genome_scores_row> MovieDatabase::setMovieTagRelevance(int movie_id, int tag_id, double relevance) {
    return this->setMovieTagRelevance({movie_id, tag_id, relevance});
}

std::unique_ptr<user_scores_row> MovieDatabase::setUserTagRelevance(int user_id, int tag_id, double relevance) {
    return this->setUserTagRelevance({user_id, tag_id, relevance});
}

/*!
 * Note that this will replace the value of all scores currently in the vector, add them if they don't exist, and ignore them  if they were unmentioned.
 * @param Vector of genome_scores_row
 * @return Vector of uniq pointers to genome_scores_row
 */
std::vector<std::unique_ptr<genome_scores_row>>
MovieDatabase::setMovieTagRelevance(const std::vector<genome_scores_row> &a) {
    std::vector<std::unique_ptr<genome_scores_row>> returnVector;
    dbPtr->transaction([&] {
        for (const auto &entry: a) {
            returnVector.push_back(setMovieTagRelevance(entry));
        }
        return true;
    });
    return returnVector;
}

/*!
 * Note that this will replace the value of all scores currently in the vector, add them if they don't exist, and ignore them  if they were unmentioned.
 * @param Vector of user_scores_row
 * @return Vector of uniq pointers to user_scores_row
 */
std::vector<std::unique_ptr<user_scores_row>>
MovieDatabase::setUserTagRelevance(const std::vector<user_scores_row> &a) {
    std::vector<std::unique_ptr<user_scores_row>> returnVector;
    dbPtr->transaction([&] {
        for (const auto &entry: a) {
            returnVector.push_back(setUserTagRelevance(entry));
        }
        return true;
    });
    return returnVector;
}

std::vector<std::unique_ptr<genome_tag_row>> MovieDatabase::getAllTags(const std::string &tag_name) const {
    try {
        return dbPtr->get_all_pointer<genome_tag_row>(where(like(&genome_tag_row::m_tag, "%" + tag_name + "%")));
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {};
}

std::vector<std::unique_ptr<genome_scores_row>>
MovieDatabase::setMovieTagRelevance(const std::vector<std::unique_ptr<genome_scores_row>> &a) {
    std::vector<std::unique_ptr<genome_scores_row>> returnVector;
    dbPtr->transaction([&] {
        for (const auto &entry: a) {
            returnVector.push_back(setMovieTagRelevance(*entry));
        }
        return true;
    });
    return returnVector;
}

std::vector<std::unique_ptr<user_scores_row>>
MovieDatabase::setUserTagRelevance(const std::vector<std::unique_ptr<user_scores_row>> &a) {
    std::vector<std::unique_ptr<user_scores_row>> returnVector;
    dbPtr->transaction([&] {
        for (const auto &entry: a) {
            returnVector.push_back(setUserTagRelevance(*entry));
        }
        return true;
    });
    return returnVector;
}

std::vector<std::vector<std::unique_ptr<genome_scores_row>>>
MovieDatabase::getMovieTagsFromWatchlist(int user_id) const {
    std::vector<std::vector<std::unique_ptr<genome_scores_row>>> returnVector;
    try {
        dbPtr->transaction([&] {
            auto moviesToFetch = this->moviesRatedByUser(user_id);
            for (const auto &i: moviesToFetch) {
                returnVector.push_back(std::move(this->getMovieTags(i->m_movie_id)));
            }
            return true;
        });
        return returnVector;
    }
    catch (std::system_error &e) {
        std::cout << e.what() << std::endl;
    }
    return {};
}

