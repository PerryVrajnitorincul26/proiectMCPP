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
    std::regex password_rx("^(?=.*[A-Z])(?=.*[!@#\\$%\\^&\\*])(?=.*\\d)[A-Za-z0-9!@#\\$%\\^&\\*]{8,}$");
    std::regex username_rx("^.{6,}$");
    std::regex country_rx("^[A-Z][a-z]+(?: [A-Z][a-z]+)*$");

    std::string username = ui->lineEdit_UsernameRegister->text().toStdString();
    std::string password = ui->lineEdit_PasswordRegister->text().toStdString();
    std::string region = ui->lineEdit_Region->text().toStdString();

    if (ui->lineEdit_UsernameRegister->text().trimmed().isEmpty() ||
        ui->lineEdit_PasswordRegister->text().trimmed().isEmpty() || ui->lineEdit_Region->text().trimmed().isEmpty()) {
        QMessageBox::information(this, "Sign Up", "Please fill in all the boxes!");
        emit noCredential();
    }

    if (!std::regex_match(username, username_rx)) {
        QMessageBox::warning(this, "Warning", "Invalid username, it must contain more than 5 characters");
        emit usedSymbols();
    } else if (!std::regex_match(password, password_rx)) {
        QMessageBox::warning(this, "Warning",
                             "Invalid password: it must be at least 8 characters length, contain 1 uppercase, 1 special character, 1 digit");
        emit usedSymbols();
    }
    else if (!std::regex_match(region, country_rx)) {
        QMessageBox::warning(this, "Warning", "Invalid country - every word must start with an uppercase.");
        emit usedSymbols();
    }
    else {
        auto &dbRef = MovieDatabase::instance();
        dbRef.signup(username, password, region);
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


