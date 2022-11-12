//
// Created by perry on 11/11/22.
//

#ifndef MCPP_MOVIEDATABASE_H
#define MCPP_MOVIEDATABASE_H

#include "db_headers.h"
#include "sqlite_orm/sqlite_orm.h"
#include <iostream>

using namespace sqlite_orm;

/*!
 * Singleton that contains a pointer to the database object.
 * @warning You should only be able to create references to this object by calling ::instance.
 */
class MovieDatabase {
private:
    MovieDatabase() {
        dbPtr = std::make_unique<Storage>(init_storage("identifier.sqlite"));
        std::cout << "database created" << std::endl;
    }


public:
    /*!
     * This should make it impossible to create anything other reference to this class. As such we avoid duplicating
     * any information regarding the database.
     */
    MovieDatabase(MovieDatabase &) = delete;

    MovieDatabase(MovieDatabase &&) = delete;

    MovieDatabase &operator=(MovieDatabase &) = delete;

    MovieDatabase &operator=(MovieDatabase &&) = delete;

    //Pointer will remain public for now mostly for testing purposes but this will at some point be changed.(hopefully)
    std::unique_ptr<Storage> dbPtr;

    static MovieDatabase &instance() {
        static std::unique_ptr<MovieDatabase> md(new MovieDatabase);
        return *md;
    }

    static MovieDatabase &movieDatabase() {
        return instance();
    }

    /*!
     * Please move this as it is initialised and never used again after calling this function
     * @param m_id id of movie object
     * @return movie_row object with corresponding m_id
     */
    std::unique_ptr<movie_row> getMovieById(int m_id) const;

    std::unique_ptr<std::vector<movie_row>> searchMovieTitles(const std::string &src) const;

    std::unique_ptr<user_row> getUserById(int u_id) const;

    std::unique_ptr<user_row> getUserByUsername(const std::string &username) const;

    bool login(const std::string &username, const std::string &password) const;

    std::unique_ptr<std::vector<user_row>> searchUsersByUsername(const std::string &src) const;


    std::unique_ptr<std::vector<user_rating_row>> getUserReviews(int u_id) const;
};

#endif //MCPP_MOVIEDATABASE_H
