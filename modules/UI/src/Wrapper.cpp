#include "Wrapper.h"
#include "ui_Wrapper.h"
#include "TMDB.h"


Wrapper::Wrapper(QWidget *parent) :
    QWidget(parent), ui(new Ui::Wrapper)
{
    ui->setupUi(this);

    QIcon mlogo("M");
    ui->minimize->setIcon(QIcon("minimize"));
    ui->close->setIcon(QIcon("close"));
    ui->mlogo->addAction(mlogo,QLineEdit::LeadingPosition);

    ui->stackedWidget->setCurrentIndex(0);
    ui->stackedWidget->insertWidget(1,&_signin);

    ui->stackedWidget->insertWidget(2, & _signup);
    ui->stackedWidget->insertWidget(4,&_usermeniu);


    connect(&_signup, &SignUp::HomeClicked, this, &Wrapper::moveHome);
    connect(&_signin, &SignIn::HomeClicked, this,&Wrapper::moveHome);
    connect(&_signin,&SignIn::Signed,this,&Wrapper::disableSignUp);
    connect(&_signup,&SignUp::SignUpClicked,this,&Wrapper::UpToIn);
    connect(&_signin, &SignIn::AccountNotFound,this,&Wrapper::InToUp);
    connect(&_signin,&SignIn::Signed,this,&Wrapper::toMeniu);
    connect(&_usermeniu,&UserMeniu::logout,this,&Wrapper::reset);
    connect(&_signin, SIGNAL(wrongInput()),this,SLOT(UpToIn()));
    connect(&_signin,SIGNAL(noCredential()),this,SLOT(InToUp()));

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

void Wrapper::toMeniu(User u) {
    this->loggedInUser=&u;
    this->_usermeniu.setCurrentUser(&u);
    ui->stackedWidget->setCurrentIndex(4);
}

void Wrapper::reset(){
    close();
}

User *Wrapper::getLoggedInUser() const {
    return loggedInUser;
}

void Wrapper::on_minimize_clicked() {
    showMinimized();
}

void Wrapper::on_close_clicked() {
    close();
}







