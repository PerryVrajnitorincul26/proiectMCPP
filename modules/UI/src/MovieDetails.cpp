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

    this->interalMovieDetails = new Movie(movieId);
    this->externalMovieDetals = new TMDB(ref.getLinkEntry(movieId)->m_tmdb_id);
    connect(externalMovieDetals, &TMDB::finishedLoading, this, &MovieDetails::loadImage);
    qDebug() << "Instantiated MovieDetails";
}


//TRIGGERS

double MovieDetails::on_GiveRating_clicked() {
    auto &ref = MovieDatabase::instance();
    reviewObj->m_rating = ui->doubleSpinBox->value();
    ref.watch(*reviewObj);
    return ui->doubleSpinBox->value();
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
    ui->titleLabel->setText(QString::fromStdString(interalMovieDetails->getTitle()));
    ui->posterLabel->setPixmap(*externalMovieDetals->pixmap);
    ui->posterLabel->setScaledContents(true);
    //ui->posterLabel->setMask(movie->pixmap->mask());
    ui->posterLabel->show();
}
