#include "Wrapper.h"
#include "ui_Wrapper.h"
#include "TMDB.h"

Wrapper::Wrapper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wrapper)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(1,&_signin);

    ui->stackedWidget->insertWidget(2, & _dialog);
    ui->stackedWidget->insertWidget(3,& _moviestable);
ui->pushButton_goMovieList->setDisabled(true);
    connect(&_dialog, SIGNAL(HomeClicked()),this,SLOT(moveHome()));
    connect(&_moviestable, SIGNAL(homeClicked()),this, SLOT(moveHome()));
    connect(&_signin, SIGNAL(HomeClicked()), this,SLOT(moveHome()));
    connect(&_signin,SIGNAL(Signed()),this, SLOT(showMovieList()));
    connect(&_signin,SIGNAL(Signed()),this,SLOT(disableSignUp()));
    connect(&_dialog,SIGNAL(SignUpClicked()),this,SLOT(UpToIn()));

}

Wrapper::~Wrapper()
{
    delete ui;
}

void Wrapper::on_pushButton_goSignIn_clicked() {
    ui->stackedWidget->setCurrentIndex(1);

}

void Wrapper::on_pushButton_goSignUp_clicked() {
ui->stackedWidget->setCurrentIndex(2);
}



void Wrapper::on_pushButton_goMovieList_clicked() {
ui->stackedWidget->setCurrentIndex(3);
}

void Wrapper::on_pushButton_back_clicked() {
    ui->stackedWidget->setCurrentIndex(0);

}

void Wrapper::moveHome() {
    ui->stackedWidget->setCurrentIndex(0);

}

void Wrapper::showMovieList() {
ui->pushButton_goMovieList->setEnabled(true);
}

void Wrapper::disableSignUp() {
ui->pushButton_goSignUp->setDisabled(true);
}

void Wrapper::UpToIn() {
    ui->stackedWidget->setCurrentIndex(1);

}

