//
// Created by perry on 11/9/22.
//
#include <string>

#ifndef MCPP_DBLIB_H
#define MCPP_DBLIB_H

class netflix_row {
public:
    virtual ~netflix_row();

public:
    int m_show_id;
    int m_release_year;
    std::string m_type;
    std::string m_title;
    std::string m_director;
    std::string m_cast;
    std::string m_country;
    std::string m_date_added;
    std::string m_rating;
    std::string m_duration;
    std::string m_listed_in;
    std::string m_description;
};


class user_row {
public:
    user_row(int mUserId, const std::string &mUsername, const std::string &mPassword, const std::string &mRegion);

private:
    int m_user_id;
    std::string m_username;
    std::string m_password;
    std::string m_region;
};

class watchlist_row {
public:
    watchlist_row(int mUserId, int mMovieId, double mRating, const std::string &mDateModified);

private:
    int m_user_id;
    int m_movie_id;
    double m_rating;
    std::string m_date_modified;
};

class user_tag_row {
public:
    user_tag_row(int mUserId, int mMovieId, const std::string &mTag, const std::string &mTimestamp);

private:
    int m_user_id;
    int m_movie_id;
    std::string m_tag;
    std::string m_timestamp;
};

class user_rating_row {
public:
    user_rating_row(int mUserId, int mMovieId, const std::string &mRating, const std::string &mTimestamp);

private:
    int m_user_id;
    int m_movie_id;
    std::string m_rating;
    std::string m_timestamp;
};

class movie_row {
public:
    movie_row(int mMovieId, const std::string &mTitle, const std::string &mGenres);

private:
    int m_movie_id;
    std::string m_title;
    std::string m_genres; //NOTE: This is a string of multiple genres associated with a film separated by "|" (pipe character)
};

class link_row {
public:
    link_row(int mMovieId, int mImbdId, int mTmdbId);

private:
    int m_movie_id;
    int m_imbd_id;
    int m_tmdb_id;
};

class genome_tag_row {
public:
    genome_tag_row(int mTagId, const std::string &mTag);

    genome_tag_row();

    int getMTagId() const;

    void setMTagId(int mTagId);

    const std::string &getMTag() const;

    void setMTag(const std::string &mTag);
private:
    int m_tag_id;
    std::string m_tag;
};

class genome_scores_row {
public:
    genome_scores_row(int mMovieId, int mTagId, double mRelevance);

private:
    int m_movie_id;
    int m_tag_id;
    double m_relevance;
};


#endif //MCPP_DBLIB_H
