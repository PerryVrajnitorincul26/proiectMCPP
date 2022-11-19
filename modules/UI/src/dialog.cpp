#include "dialog.h"
#include "ui_dialog.h"
#include "User.h"
#include "QMessageBox"
#include "MovieDatabase.h"

Dialog::Dialog(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::Dialog) {
    ui->setupUi(this);
}

Dialog::~Dialog() {
    delete ui;

}

void Dialog::on_pushButton_SignUp_clicked() {
    auto &dbRef = MovieDatabase::instance();
    dbRef.signup(ui->lineEdit_UsernameRegister->text().toStdString(),
                 ui->lineEdit_PasswordRegister->text().toStdString(),
                 ui->lineEdit_Region->text().toStdString());
}

