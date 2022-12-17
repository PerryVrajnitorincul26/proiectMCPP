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

    ui->stackedWidget->insertWidget(2, & _signup);
    ui->stackedWidget->insertWidget(3,& _moviestable);
    ui->stackedWidget->insertWidget(4,&_usermeniu);
ui->pushButton_goMovieList->setDisabled(true);
    connect(&_signup, SIGNAL(HomeClicked()),this,SLOT(moveHome()));
    connect(&_moviestable, SIGNAL(homeClicked()),this, SLOT(moveHome()));
    connect(&_signin, SIGNAL(HomeClicked()), this,SLOT(moveHome()));
    connect(&_signin,SIGNAL(Signed()),this, SLOT(showMovieList()));
    connect(&_signin,SIGNAL(Signed()),this,SLOT(disableSignUp()));
    connect(&_signup,SIGNAL(SignUpClicked()),this,SLOT(UpToIn()));
    connect(&_signin, SIGNAL(AccountNotFound()),this,SLOT(InToUp()));
   // connect(&_signin,SIGNAL(Signed()),this,SLOT(moveHome()));
   connect(&_signin,SIGNAL(Signed()),this,SLOT(toMeniu()));
   connect(&_usermeniu,SIGNAL(logout()),this,SLOT(reset()));

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

void Wrapper::InToUp() {
ui->stackedWidget->setCurrentIndex(2);
}

void Wrapper::toMeniu() {
ui->stackedWidget->setCurrentIndex(4);
}

void Wrapper::reset(){
    close();

}

