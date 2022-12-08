//
// Created by perry on 11/11/22.
//

#ifndef MCPP_MOVIEDATABASE_H
#define MCPP_MOVIEDATABASE_H

#include "db_headers.h"
#include "sqlite_orm/sqlite_orm.h"
#include <iostream>

using namespace sqlite_orm;


#define STRINGIFY(x) #x
#define STR(y) STRINGIFY(y)
#ifndef dbfile
#error  dbfile MUST Be defined
#endif

/*!
 * Singleton that contains a pointer to the database object.
 * @warning You should only be able to create references to this object by calling ::instance.
 */
class MovieDatabase {
private:
    MovieDatabase() {
        dbPtr = std::make_unique<Storage>(init_storage((STR(dbfile))));
        std::cout << "database created" << std::endl;
    }

    explicit MovieDatabase(const std::string &customPath) {
        dbPtr = std::make_unique<Storage>(init_storage(customPath));
        std::cout << "database created" << std::endl;
    }

public:
    /*!
     * This should make it impossible to create anything other than references to this class. As such we avoid duplicating
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

    static MovieDatabase &instance(const std::string &path) {
        static std::unique_ptr<MovieDatabase> md(new MovieDatabase(path));
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
    [[nodiscard]] std::unique_ptr<movie_row> getMovieById(int m_id) const;

    [[nodiscard]] std::vector<std::unique_ptr<movie_row>> searchMovieTitles(const std::string &src) const;

    [[nodiscard]] std::vector<std::unique_ptr<movie_row>> searchMovieGenres(const std::string &src) const;

    [[nodiscard]] std::unique_ptr<user_row> getUserById(int u_id) const;

    [[nodiscard]] std::unique_ptr<user_row> getUserByUsername(const std::string &username) const;

    [[nodiscard]] std::unique_ptr<user_row> login(const std::string &username, const std::string &password) const;

    [[nodiscard]] std::unique_ptr<std::vector<user_row>> searchUsersByUsername(const std::string &src) const;

    [[nodiscard]] std::unique_ptr<std::vector<user_rating_row>> getUserReviews(int u_id) const;

    [[nodiscard]] std::unique_ptr<user_rating_row> getWatchEntry(int u_id, int m_id) const;

    [[nodiscard]] std::unique_ptr<std::vector<watchlist_row>> watchlistByUser(int u_id) const;

    [[nodiscard]] std::vector<std::unique_ptr<movie_row>> moviesRatedByUser(int u_id) const;

    [[nodiscard]] std::vector<std::unique_ptr<community_tag_row>> tagsByUser(int u_id) const;

    [[nodiscard]] std::unique_ptr<link_row> getLinkEntry(int m_id) const;

    [[nodiscard]] std::unique_ptr<genome_tag_row> getTagName(int tag_id) const;

//    [[nodiscard]] std::unique_ptr<genome_tag_row> getTagId(const std::string & tag_name) const;

    [[nodiscard]] std::vector<std::unique_ptr<genome_tag_row>> getAllTags(const std::string &tag_name = "") const;

    [[nodiscard]] std::unique_ptr<genome_scores_row> getMovieTagRelevance(int tag_id, int movie_id) const;

    [[nodiscard]] std::unique_ptr<user_scores_row> getUserTagRelevance(int tag_id, int movie_id) const;

    [[nodiscard]] std::vector<std::unique_ptr<genome_scores_row>> getMovieTags(int movie_id) const;

    [[nodiscard]] std::vector<std::unique_ptr<user_scores_row>> getUserTags(int user_id) const;

    [[nodiscard]] std::vector<std::vector<std::unique_ptr<genome_scores_row>>> getMovieTagsFromWatchlist(int user_id) const;

    [[nodiscard]] std::unique_ptr<genome_scores_row> setMovieTagRelevance(const genome_scores_row &rhs);

    [[nodiscard]] std::unique_ptr<user_scores_row> setUserTagRelevance(int user_id, int tag_id, double relevance);

    [[nodiscard]] std::unique_ptr<genome_scores_row> setMovieTagRelevance(int movie_id, int tag_id, double relevance);

    [[nodiscard]] std::vector<std::unique_ptr<genome_scores_row>>
    setMovieTagRelevance(const std::vector<genome_scores_row> &a);

    [[nodiscard]] std::vector<std::unique_ptr<user_scores_row>> setUserTagRelevance(
            const std::vector<user_scores_row> &a);

    [[nodiscard]] std::vector<std::unique_ptr<genome_scores_row>>
    setMovieTagRelevance(const std::vector<std::unique_ptr<genome_scores_row>> &a);

    [[nodiscard]] std::vector<std::unique_ptr<user_scores_row>> setUserTagRelevance(
            const std::vector<std::unique_ptr<user_scores_row>> &a);

    [[nodiscard]] std::unique_ptr<user_scores_row> setUserTagRelevance(const user_scores_row &rhs);

    [[nodiscard]] std::unique_ptr<user_row> signup(const user_row &user) const;

    [[nodiscard]] std::unique_ptr<user_row>
    signup(const std::string &username, const std::string &password, const std::string &region = "Romania") const;

    [[nodiscard]] std::unique_ptr<community_tag_row> addCommunityTag(const community_tag_row &tagRow) const;

    [[nodiscard]] std::unique_ptr<community_tag_row>
    addCommunityTag(int user_id, int movie_id, const std::string &tag, const std::string &timestamp = "ieri") const;

    [[nodiscard]] std::unique_ptr<user_rating_row> watch(const user_rating_row &entry) const;

    [[nodiscard]] std::unique_ptr<user_rating_row>
    watch(int user_id, int movie_id, double rating, const std::string &date_modified = "none") const;


};

#endif //MCPP_MOVIEDATABASE_H
