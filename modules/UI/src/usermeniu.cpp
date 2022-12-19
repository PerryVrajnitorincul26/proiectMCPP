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




