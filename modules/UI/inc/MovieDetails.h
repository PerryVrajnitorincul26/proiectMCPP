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

class MovieDetails : public QWidget {
Q_OBJECT

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
    //Movie Data JSON format
    //adult - boolean
    bool m_adult = true; //In Qt, boolean values are represented using the bool type from the C++ standard library. The bool type can have one of two values: true or false.
    //budget - floating number
    double m_budget = 0;
    //overview - string
    QString m_overview = "This is supposed to be a description";
    //popularity - floating number
    double m_popularity = 0;
    //poster_path - string
    QString m_posterPath = "/thePosterPathOfTheMovie";
    //release_date - dateformat yyyy-mm-dd
    QDate m_releaseDate; //documentation here: https://doc.qt.io/qt-6/qdate.html#QDate-6
    //revenue - floating number
    double m_revenue = 0;
    //runtime - number (minutes)
    double m_runtime = 0;
    //Movie's poster
    QPixmap *pixmap = nullptr;

    explicit MovieDetails(QWidget *parent = nullptr);

    explicit MovieDetails(int movieId, int userId, QWidget *parent = nullptr);

    double on_GiveRating_clicked();

    void setMovieLayoutDetails(); //this functions displays the title and description in UI

    ~MovieDetails() override;

    void setTMDBdetails();

private:
    Ui::MovieDetails *ui;
    SignIn _signin;


public slots:
    void loadImage();
};


#endif //MCPP_MOVIEDETAILS_H
