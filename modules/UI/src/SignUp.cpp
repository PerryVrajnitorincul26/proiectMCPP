#include "SignUp.h"
#include "ui_SignUp.h"
#include "QMessageBox"
#include "MovieDatabase.h"

//CONSTRUCTORS
SignUp::SignUp(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::SignUp) {
    ui->setupUi(this);

    ui->lineEdit_PasswordRegister->setEchoMode(QLineEdit::Password);
    QIcon lineEdit_PasswordRegister("password");
    QIcon lineEdit_UsernameRegister("username");
    QIcon lineEdit_Region("region");
    ui->lineEdit_UsernameRegister->addAction(lineEdit_UsernameRegister, QLineEdit::LeadingPosition);
    ui->lineEdit_PasswordRegister->addAction(lineEdit_PasswordRegister, QLineEdit::LeadingPosition);
    ui->lineEdit_Region->addAction(lineEdit_Region, QLineEdit::LeadingPosition);
}

//GETTERS

//SETTERS

//OTHER METHODS

//BUTTONS
void SignUp::on_pushButton_SignUp_clicked() {
    if (ui->lineEdit_UsernameRegister->text().trimmed().isEmpty() || ui->lineEdit_PasswordRegister->text().trimmed().isEmpty() || ui->lineEdit_Region->text().trimmed().isEmpty())
    {QMessageBox::information(this, "Sign Up", "Please fill in all the boxes!");
        emit noCredential();}
    else {
        auto &dbRef = MovieDatabase::instance();
        dbRef.signup(ui->lineEdit_UsernameRegister->text().toStdString(),
                     ui->lineEdit_PasswordRegister->text().toStdString(),
                     ui->lineEdit_Region->text().toStdString());
        emit SignUpClicked();
    }
    ui->lineEdit_UsernameRegister->clear();
    ui->lineEdit_PasswordRegister->clear();
    ui->lineEdit_Region->clear();
}

void SignUp::on_pushButton_home_clicked() {
    emit HomeClicked();

}

//DESTRUCTORS
SignUp::~SignUp() {
    delete ui;

}


