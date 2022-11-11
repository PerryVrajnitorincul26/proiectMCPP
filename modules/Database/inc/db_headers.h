//
// Created by perry on 11/9/22.
//
/*!
 *  Inline functions are the best way to instantiate templates generated by sqlite_orm without an abnormally large
 *  declaration
 *  @warning: despide the null constructor being sufficient we currently get templete errors if it's not user defined
 *  @see https://github.com/fnc12/sqlite_orm/wiki/FAQ
 */

#include <string>
#include<sqlite_orm/sqlite_orm.h>

#ifndef MCPP_DBLIB_H
#define MCPP_DBLIB_H
using namespace sqlite_orm;


class user_row {
public:
    user_row(int mUserId, const std::string &mUsername, const std::string &mPassword, const std::string &mRegion);

    user_row();

    int m_user_id;
    std::string m_username;
    std::string m_password;
    std::string m_region;
};

inline auto user_table() {
    return make_table("user",
                      make_column("user_id", &user_row::m_user_id),
                      make_column("username", &user_row::m_username),
                      make_column("password", &user_row::m_password),
                      make_column("region", &user_row::m_region)
    );
}

class watchlist_row {
public:
    watchlist_row(int mUserId, int mMovieId, double mRating, const std::string &mDateModified);

    watchlist_row();

    int m_user_id;
    int m_movie_id;
    double m_rating;
    std::string m_date_modified;
};

inline auto watchlist_table() {
    return make_table("watchlist",
                      make_column("user_id", &watchlist_row::m_user_id),
                      make_column("movie_id", &watchlist_row::m_movie_id),
                      make_column("rating", &watchlist_row::m_rating),
                      make_column("date_modified", &watchlist_row::m_date_modified)
    );
}

class community_tag_row {
public:
    community_tag_row(int mUserId, int mMovieId, const std::string &mTag, const std::string &mTimestamp);

    community_tag_row();

    int m_user_id;
    int m_movie_id;
    std::string m_tag;
    std::string m_timestamp;
};

inline auto community_tag_table() {
    return make_table("community_tag",
                      make_column("user_id", &community_tag_row::m_user_id),
                      make_column("movie_id", &community_tag_row::m_movie_id),
                      make_column("tag", &community_tag_row::m_tag),
                      make_column("timestamp", &community_tag_row::m_timestamp)
    );
}

class user_rating_row {
public:
    user_rating_row(int mUserId, int mMovieId, const std::string &mRating, const std::string &mTimestamp);

    user_rating_row();

    int m_user_id;
    int m_movie_id;
    std::string m_rating;
    std::string m_timestamp;
};

inline auto rating_table() {
    return make_table(
            "rating", //TODO: this is a name mismatch and i'd like it fixed in the DB since user_rating is clearer.
            make_column("user_id", &user_rating_row::m_user_id),
            make_column("movie_id", &user_rating_row::m_movie_id),
            make_column("rating", &user_rating_row::m_rating),
            make_column("timestamp", &user_rating_row::m_timestamp)
    );
}

class movie_row {
public:
    movie_row(int mMovieId, const std::string &mTitle, const std::string &mGenres);

    movie_row();

    int m_movie_id;
    std::string m_title;
    std::string m_genres; //NOTE: This is a string of multiple genres associated with a film separated by "|" (pipe character)
};

inline auto movie_table() {
    return make_table("movie",
                      make_column("movie_id", &movie_row::m_movie_id),
                      make_column("title", &movie_row::m_title),
                      make_column("genres", &movie_row::m_genres)
    );
}


class link_row {
public:
    link_row(int mMovieId, int mImbdId, int mTmdbId);

    link_row();

    int m_movie_id;
    int m_imbd_id;
    int m_tmdb_id;
};

inline auto link_table() {
    return make_table("link",
                      make_column("movie_id", &link_row::m_movie_id),
                      make_column("imdb_id", &link_row::m_imbd_id),
                      make_column("tmdb_id", &link_row::m_tmdb_id)
    );
}

class genome_tag_row {
public:
    genome_tag_row(int mTagId, const std::string &mTag);

    genome_tag_row();

    int m_tag_id;
    std::string m_tag;
};


inline auto genome_tag_table() {
    return make_table("genome_tags",
                      make_column("tag_id", &genome_tag_row::m_tag_id),
                      make_column("tag", &genome_tag_row::m_tag)
    );
}

class genome_scores_row {
public:
    genome_scores_row(int mMovieId, int mTagId, double mRelevance);

    genome_scores_row();

    int m_movie_id;
    int m_tag_id;
    double m_relevance;
};

inline auto genome_scores_table() {
    return make_table("genome_scores",
                      make_column("movie_id", &genome_scores_row::m_movie_id),
                      make_column("tag_id", &genome_scores_row::m_tag_id),
                      make_column("relevance", &genome_scores_row::m_relevance)
    );
}

inline auto init_storage(const std::string &path) {
    return make_storage(path, user_table(), watchlist_table(), community_tag_table(), rating_table(), movie_table(),
                        link_table(), genome_tag_table(), genome_scores_table());
}

using Storage = decltype(init_storage(""));



#endif //MCPP_DBLIB_H
