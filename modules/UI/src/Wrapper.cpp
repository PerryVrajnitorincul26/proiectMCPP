#include "Wrapper.h"
#include "ui_Wrapper.h"
#include "TMDB.h"

Wrapper::Wrapper(QWidget *parent) :
    QWidget(parent), ui(new Ui::Wrapper)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(1,&_signin);

    ui->stackedWidget->insertWidget(2, & _signup);
    ui->stackedWidget->insertWidget(4,&_usermeniu);
    connect(&_signup, SIGNAL(HomeClicked()),this,SLOT(moveHome()));
    connect(&_signin, SIGNAL(HomeClicked()), this,SLOT(moveHome()));
    connect(&_signin,SIGNAL(Signed()),this,SLOT(disableSignUp()));
    connect(&_signup,SIGNAL(SignUpClicked()),this,SLOT(UpToIn()));
    connect(&_signin, SIGNAL(AccountNotFound()),this,SLOT(InToUp()));
//    connect(&_signin, &SignIn::AccountFound, this, [this](User &u){
//        setLoggedInUser(u);
//        qDebug()<<QString::fromStdString(this->loggedInUser.GetUsername())<<" is logged in YEEEE";
//    });
//    connect(&_signin,SIGNAL(Signed()),this,SLOT(moveHome()));
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

void Wrapper::on_pushButton_back_clicked() {
    ui->stackedWidget->setCurrentIndex(0);

}

void Wrapper::moveHome() {
    ui->stackedWidget->setCurrentIndex(0);

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

User *Wrapper::getLoggedInUser() const {
    return loggedInUser;
}

void Wrapper::setLoggedInUser(User *loggedInUser) {
    Wrapper::loggedInUser = loggedInUser;
}





