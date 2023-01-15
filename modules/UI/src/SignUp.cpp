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
    std::regex username_rx("^.{6,}$");
    std::regex password_rx("^(?=.*[A-Za-z])(?=.*\\d)(?=.*[@$!%*#?&])[A-Za-z\\d@$!%*#?&]{8,}$");

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
        QMessageBox::warning(this, "Warning",
                             "Invalid username, please type in more than 6 characters");
        emit usedSymbols();
    } else if (!std::regex_match(password, password_rx)) {
        QMessageBox::warning(this, "Warning",
                             "Password must contain at least one uppercase letter, one special character, one digit, and be at least 8 characters long.");
        emit usedSymbols();
    } else if (!std::regex_match(region, country_rx)) {
        QMessageBox::warning(this, "Warning",
                             "Please enter a valid country! The first letter must be an uppercase, the following letters must be lowercase. The country name can be composed of one"
                             "or more words, each starts with an uppercase letter, and the following letters are lowercase");
        emit usedSymbols();
    } else {
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


