//
// Created by Codrut on 11/27/2022.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MovieDetails.h" resolved

#include "moviedetails.h"
#include "ui_MovieDetails.h"


MovieDetails::MovieDetails(QWidget *parent) :
        QWidget(parent), ui(new Ui::MovieDetails) {
    ui->setupUi(this);
}

MovieDetails::~MovieDetails() {
    delete ui;
}

double MovieDetails::on_pushButton_clicked() {
    return ui->doubleSpinBox->value();
}
