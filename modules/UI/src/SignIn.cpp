#include "SignIn.h"
#include "./ui_SignIn.h"
#include "QMessageBox"
#include "SignUp.h"
#include "db_headers.h"
#include "MovieDatabase.h"
#include <QHBoxLayout>
#include "MoviesTable.h"


SignIn::SignIn(QWidget* parent)
	: QWidget(parent)
	, ui(new Ui::SignIn)
{
    ui->setupUi(this);

}

SignIn::~SignIn()
{
    delete ui;
}


void SignIn::on_pushButton_SignIn_clicked()
{
    auto &dbRef = MovieDatabase::instance();
    auto response = dbRef.login(ui->lineEdit_user->text().toStdString(),ui->lineEdit_pass->text().toStdString());

    verifyInputFields();
    verifyExistingUser();

    if(response == nullptr) {

       emit AccountNotFound();
    }
    else{
        this->current_user = std::move(response);
    }

}

void SignIn::verifyInputFields() {
    if(ui->lineEdit_user->text().toStdString().empty() && ui->lineEdit_pass->text().toStdString().empty())
        QMessageBox::information(this, "Login Error", "Please insert username and password");
    else if(ui->lineEdit_user->text().toStdString().empty())
        QMessageBox::information(this, "Login Error", "Please insert username");
    else if(ui->lineEdit_pass->text().toStdString().empty())
        QMessageBox::information(this, "Login Error", "Please insert password");
}

void SignIn::verifyExistingUser() {
    logged=false;
    auto &dbRef = MovieDatabase::instance();
    auto response = dbRef.login(ui->lineEdit_user->text().toStdString(),ui->lineEdit_pass->text().toStdString());

    if(response == nullptr) {
        QMessageBox::information(this, "Login Error", "Account not found - create one!");

    }

    else
    { QMessageBox::information(this, "Login successful", "Account was found!");

        logged=true;
    }

    if(logged==true)
    {
        emit Signed();
    }


}

void SignIn::on_searchDemo_clicked() {
    MoviesTable moviesTable(this);
    moviesTable.setModal(true);
    moviesTable.exec();
}

void SignIn::on_pushButton_back_clicked() {
    emit HomeClicked();

}

bool SignIn::isLogged()  {
    return logged;
}


