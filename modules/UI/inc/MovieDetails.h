//
// Created by Codrut on 11/27/2022.
//

#ifndef MCPP_MOVIEDETAILS_H
#define MCPP_MOVIEDETAILS_H

#include <QWidget>
#include <MovieDatabase.h>
#include <db_headers.h>
#include "TMDB.h"
#include "Movie.h"
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

    Movie* interalMovieDetails; //this points to the movie details stored in our local database and saved in Movie class
    TMDB *externalMovieDetals; //this points to the TMDB class which stores the details received from TMDB Api

    explicit MovieDetails(QWidget *parent = nullptr);

    explicit MovieDetails(int movieId, int userId, QWidget *parent = nullptr);

    double on_GiveRating_clicked();

    void setMovieLayoutDetails(); //this functions displays the title and description in UI

    ~MovieDetails() override;

private:
    Ui::MovieDetails *ui;
    SignIn _signin;

public slots:
    void loadImage();
};


#endif //MCPP_MOVIEDETAILS_H
