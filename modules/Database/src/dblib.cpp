//
// Created by perry on 11/9/22.
//

#include <iostream>
#include "dblib.h"

user_row::user_row(int mUserId, const std::string &mUsername, const std::string &mPassword, const std::string &mRegion)
        : m_user_id(mUserId), m_username(mUsername), m_password(mPassword), m_region(mRegion) {}

watchlist_row::watchlist_row(int mUserId, int mMovieId, double mRating, const std::string &mDateModified) : m_user_id(
        mUserId), m_movie_id(mMovieId), m_rating(mRating), m_date_modified(mDateModified) {}

user_tag_row::user_tag_row(int mUserId, int mMovieId, const std::string &mTag, const std::string &mTimestamp)
        : m_user_id(mUserId), m_movie_id(mMovieId), m_tag(mTag), m_timestamp(mTimestamp) {}

user_rating_row::user_rating_row(int mUserId, int mMovieId, const std::string &mRating, const std::string &mTimestamp)
        : m_user_id(mUserId), m_movie_id(mMovieId), m_rating(mRating), m_timestamp(mTimestamp) {}

movie_row::movie_row(int mMovieId, const std::string &mTitle, const std::string &mGenres) : m_movie_id(mMovieId),
                                                                                            m_title(mTitle),
                                                                                            m_genres(mGenres) {}

link_row::link_row(int mMovieId, int mImbdId, int mTmdbId) : m_movie_id(mMovieId), m_imbd_id(mImbdId),
                                                             m_tmdb_id(mTmdbId) {}

genome_tag_row::genome_tag_row(int mTagId, const std::string &mTag) : m_tag_id(mTagId), m_tag(mTag) {}

int genome_tag_row::getMTagId() const {
    return m_tag_id;
}

void genome_tag_row::setMTagId(int mTagId) {
    m_tag_id = mTagId;
}

const std::string &genome_tag_row::getMTag() const {
    return m_tag;
}

void genome_tag_row::setMTag(const std::string &mTag) {
    m_tag = mTag;
}

genome_tag_row::genome_tag_row() {
}

genome_scores_row::genome_scores_row(int mMovieId, int mTagId, double mRelevance) : m_movie_id(mMovieId),
                                                                                    m_tag_id(mTagId),
                                                                                    m_relevance(mRelevance) {}
