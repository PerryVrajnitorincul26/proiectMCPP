//
// Created by Codrut on 11/27/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MovieDetails.h" resolved

#include "moviedetails.h"
#include "ui_moviedetails.h"


MovieDetails::MovieDetails(QWidget *parent) :
        QWidget(parent), ui(new Ui::MovieDetails) {
    ui->setupUi(this);
}

MovieDetails::~MovieDetails() {
    delete ui;
}

double MovieDetails::on_GiveRating_clicked() {
    auto &ref = MovieDatabase::instance();
    reviewObj->m_rating = ui->doubleSpinBox->value();
    ref.watch(*reviewObj);
    return ui->doubleSpinBox->value();
}

MovieDetails::MovieDetails(int mid, int cid, QWidget *parent) : MovieDetails(parent) {
    auto &ref = MovieDatabase::instance();
    this->reviewObj = ref.getWatchEntry(cid, mid);
    if (this->reviewObj == nullptr) {
        this->reviewObj = std::make_unique<user_rating_row>(user_rating_row(cid, mid, 0.0f));
    }
}
