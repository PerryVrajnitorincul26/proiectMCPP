//
// Created by Codrut on 11/27/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MovieDetails.h" resolved

#include "MovieDetails.h"
#include "ui_MovieDetails.h"
#include "TMDB.h"

//CONSTRUCTORS
MovieDetails::MovieDetails(QWidget *parent) :
        QWidget(parent), ui(new Ui::MovieDetails) {
    ui->setupUi(this);
    update();
}

MovieDetails::~MovieDetails() {
    delete ui;
}

MovieDetails::MovieDetails(int movieId, int userId, QWidget *parent) : MovieDetails(parent) {
    auto &ref = MovieDatabase::instance();
    this->reviewObj = ref.getWatchEntry(userId, movieId);

    if (this->reviewObj == nullptr) {
        this->reviewObj = std::make_unique<user_rating_row>(user_rating_row(userId, movieId, 0.0f));
    }

    auto fromDb = ref.getMovieById(movieId);

    this->m_title = fromDb->m_title;
    this->m_genres = fromDb->m_genres;
    this->tmdb_id = ref.getLinkEntry(movieId)->m_tmdb_id;

    //this->m_userReview = ?; TO DO

    this->externalMovieDetals = new TMDB(ref.getLinkEntry(movieId)->m_tmdb_id);

    connect(externalMovieDetals, &TMDB::finishedLoading, this, &MovieDetails::loadImage);
    qDebug() << "Instantiated MovieDetails";
}


//TRIGGERS

double MovieDetails::on_GiveRating_clicked() {
       bool logged=_signin.isLogged();
    if (logged==true) {
        auto &ref = MovieDatabase::instance();
        reviewObj->m_rating = ui->doubleSpinBox->value();
        ref.watch(*reviewObj);

        return ui->doubleSpinBox->value();
    }
    else

        QMessageBox::warning(this,"Acces denied!","Log in first!");
}


//FUNCTIONS
void MovieDetails::loadImage() {
    auto movie = qobject_cast<TMDB *>(sender());

    if (movie->pixmap == nullptr)
        qDebug() << "Image not loaded...";
    else {
//        ui->posterLabel->setPixmap(*movie->pixmap);
//        ui->posterLabel->setScaledContents(true);
//        //ui->posterLabel->setMask(movie->pixmap->mask());
//        ui->posterLabel->show();
        setMovieLayoutDetails();
    }

}

void MovieDetails::setMovieLayoutDetails() {

    ui->descriptionLabel->setWordWrap(true);
    ui->descriptionLabel->setText(externalMovieDetals->getOverview());
    ui->descriptionLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    ui->descriptionLabel->adjustSize();
    ui->titleLabel->setText(QString::fromStdString(this->m_title));
    ui->posterLabel->setPixmap(*externalMovieDetals->pixmap);
    ui->posterLabel->setScaledContents(true);
    //ui->posterLabel->setMask(movie->pixmap->mask());
    ui->posterLabel->show();
}

void MovieDetails::setTMDBdetails() {

}

const std::unique_ptr<user_rating_row> &MovieDetails::getReviewObj() const {
    return reviewObj;
}

const std::string &MovieDetails::getMTitle() const {
    return m_title;
}

const std::string &MovieDetails::getMGenres() const {
    return m_genres;
}

/*void MovieDetails::setReviewObj(const std::unique_ptr<user_rating_row> &reviewObj) {
    MovieDetails::reviewObj = reviewObj;
}*/

void MovieDetails::setMTitle(const std::string &mTitle) {
    m_title = mTitle;
}

void MovieDetails::setMGenres(const std::string &mGenres) {
    m_genres = mGenres;
}

void MovieDetails::setMUserReview(double mUserReview) {
    m_userReview = mUserReview;
}

double MovieDetails::getMUserReview() const {
    return m_userReview;
}


