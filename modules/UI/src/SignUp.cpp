#include "SignUp.h"
#include "ui_SignUp.h"
#include "QMessageBox"
#include "MovieDatabase.h"

SignUp::SignUp(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SignUp) {
        ui->setupUi(this);

    ui->lineEdit_PasswordRegister->setEchoMode(QLineEdit::Password);
    QIcon lineEdit_PasswordRegister("password");
    QIcon lineEdit_UsernameRegister("username");
    QIcon lineEdit_Region("region");
    ui->lineEdit_UsernameRegister->addAction(lineEdit_UsernameRegister,QLineEdit::LeadingPosition);
    ui->lineEdit_PasswordRegister->addAction(lineEdit_PasswordRegister,QLineEdit::LeadingPosition);
    ui->lineEdit_Region->addAction(lineEdit_Region,QLineEdit::LeadingPosition);
}

SignUp::~SignUp() {
    delete ui;

}

void SignUp::on_pushButton_SignUp_clicked() {
    auto &dbRef = MovieDatabase::instance();
    dbRef.signup(ui->lineEdit_UsernameRegister->text().toStdString(),
                 ui->lineEdit_PasswordRegister->text().toStdString(),
                 ui->lineEdit_Region->text().toStdString());
    emit SignUpClicked();

}

void SignUp::on_pushButton_home_clicked() {
    emit HomeClicked();

}




