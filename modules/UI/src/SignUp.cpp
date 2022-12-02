#include "SignUp.h"
#include "ui_SignUp.h"
#include "QMessageBox"
#include "MovieDatabase.h"

SignUp::SignUp(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SignUp) {
        ui->setupUi(this);
}

SignUp::~SignUp() {
    delete ui;

}

void SignUp::on_pushButton_SignUp_clicked() {
    auto &dbRef = MovieDatabase::instance();
    dbRef.signup(ui->lineEdit_UsernameRegister->text().toStdString(),
                 ui->lineEdit_PasswordRegister->text().toStdString(),
                 ui->lineEdit_Region->text().toStdString());

}

void SignUp::on_pushButton_home_clicked() {
    emit HomeClicked();

}




