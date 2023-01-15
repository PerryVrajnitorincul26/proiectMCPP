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
    std::regex rx("^[a-zA-Z][a-zA-Z0-9_]{7,}$");
    std::string username = ui->lineEdit_UsernameRegister->text().toStdString();
    std::string password= ui->lineEdit_PasswordRegister->text().toStdString();
    std::string region=ui->lineEdit_Region->text().toStdString();

    if (ui->lineEdit_UsernameRegister->text().trimmed().isEmpty() || ui->lineEdit_PasswordRegister->text().trimmed().isEmpty() || ui->lineEdit_Region->text().trimmed().isEmpty())
    {QMessageBox::information(this, "Sign Up", "Please fill in all the boxes!");
        emit noCredential();}

    if (!std::regex_match(username, rx) || !std::regex_match(password, rx) ) {
        QMessageBox::warning(this, "Warning", "Invalid input, must start with letter, have at least 8 characters, only letter,numbers and underscore are allowed.");        emit usedSymbols();
    }

    else {
        auto &dbRef = MovieDatabase::instance();
        dbRef.signup(username,password,region);
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


