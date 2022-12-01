#include "wrapper.h"
#include "ui_wrapper.h"

Wrapper::Wrapper(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Wrapper)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(2, & _dialog);
    ui->stackedWidget->insertWidget(3,& _moviestable);
    connect(&_dialog, SIGNAL(HomeClicked()),this,SLOT(moveHome()));
    connect(&_moviestable, SIGNAL(homeClicked()),this, SLOT(moveHome()));
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
