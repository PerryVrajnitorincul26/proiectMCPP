//
// Created by Codrut on 11/27/2022.
//

#ifndef MCPP_MOVIEDETAILS_H
#define MCPP_MOVIEDETAILS_H

#include <QWidget>
#include <MovieDatabase.h>
#include <db_headers.h>
#include "TMDB.h"
#include "SignIn.h"
#include "QMessageBox"


QT_BEGIN_NAMESPACE
namespace Ui { class MovieDetails; }
QT_END_NAMESPACE

class MovieDetails : public QWidget{
Q_OBJECT

private:
    Ui::MovieDetails *ui;
    SignIn _signin;

    std::unique_ptr<user_rating_row> reviewObj;

public:
    uint32_t movieId;
    uint32_t userId;

    //Internal Details
    std::string m_title;
    std::string m_genres;
    double m_userReview;

    TMDB *externalMovieDetals; //this points to the TMDB class which stores the details received from TMDB Api

    int tmdb_id;

    bool m_adult = true;

    double m_budget = 0;

    QString m_overview = "This is supposed to be a description";

    double m_popularity = 0;

    QString m_posterPath = "/thePosterPathOfTheMovie";

    QDate m_releaseDate;

    double m_revenue = 0;

    double m_runtime = 0;

    QPixmap *pixmap = nullptr;

    //CONSTRUCTORS
    explicit MovieDetails(QWidget *parent = nullptr);

    explicit MovieDetails(int movieId, int userId, QWidget *parent = nullptr);

    double on_GiveRating_clicked();

    //GETTERS
    const std::unique_ptr<user_rating_row> &getReviewObj() const;

    const std::string &getTitle() const;

    const std::string &getGenres() const;

    double getUserReview() const;

    //SETTERS
    void setMovieLayoutDetails(); //this functions displays the title and description in UI

    void setTitle(const std::string &mTitle);

    void setGenres(const std::string &mGenres);

    void setUserReview(double mUserReview);

    //DESTRUCTOR
    ~MovieDetails() override;

public slots:
    void loadImage();
};


#endif //MCPP_MOVIEDETAILS_H
