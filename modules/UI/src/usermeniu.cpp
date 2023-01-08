#include "usermeniu.h"
#include "ui_usermeniu.h"
#include "Wrapper.h"

UserMeniu::UserMeniu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserMeniu)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    //auto wrapperParent = qobject_cast<Wrapper*>(this->parent());
    ui->stackedWidget->insertWidget(1, & _movies);
    connect(&_movies, SIGNAL(homeClicked()),this,SLOT(on_backHome()));
connect(&_signin,SIGNAL(Signed()),this,SLOT(showUser()));

}

UserMeniu::~UserMeniu()
{
    delete ui;
}

void UserMeniu::on_pushButton_LogOut_clicked() {
  emit logout();

}

void UserMeniu::on_pushButton_showMovieList_clicked() {
    ui->stackedWidget->setCurrentIndex(1);

}

void UserMeniu::on_backHome() {
    ui->stackedWidget->setCurrentIndex(0);

}

void UserMeniu::on_pushButton_sett_clicked() {
ui->stackedWidget->setCurrentIndex(3);
}

void UserMeniu::on_pushButton_recom_clicked() {
ui->stackedWidget->setCurrentIndex(2);
}

void UserMeniu::on_settingsBackButt_clicked() {
    ui->stackedWidget->setCurrentIndex(0);

}

void UserMeniu::on_deleteButton_clicked() {
    emit deleteAcc();

}

void UserMeniu::on_backButtRec_clicked() {
    ui->stackedWidget->setCurrentIndex(0);

}

void UserMeniu::showUser() {
    auto &dbRef = MovieDatabase::instance();
    ui->usernameLabel->setText("Hello (USERname)");
}






