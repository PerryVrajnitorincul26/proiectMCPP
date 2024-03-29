#include "SignIn.h"
#include "./ui_SignIn.h"
#include "QMessageBox"
#include "SignUp.h"
#include "db_headers.h"
#include "MovieDatabase.h"
#include <QHBoxLayout>
#include "MoviesTable.h"
#include "Wrapper.h"

//CONSTRUCTORS
SignIn::SignIn(QWidget *parent)
        : QWidget(parent), ui(new Ui::SignIn) {
    ui->setupUi(this);
    ui->lineEdit_pass->setEchoMode(QLineEdit::Password);
    QIcon lineEdit_pass("password");
    QIcon lineEdit_user("username");
    ui->lineEdit_user->addAction(lineEdit_user, QLineEdit::LeadingPosition);
    ui->lineEdit_pass->addAction(lineEdit_pass, QLineEdit::LeadingPosition);


}

//GETTERS

//SETTERS

//OTHER METHODS



void SignIn::verifyExistingUser() {

    logged = false;

    auto &dbRef = MovieDatabase::instance();
    auto response = dbRef.login(ui->lineEdit_user->text().toStdString(), ui->lineEdit_pass->text().toStdString());

    if (response == nullptr) {
        QMessageBox::information(this, "Login Error", "Account not found - create one!");

    } else {
        /*QMessageBox::information(this, "Login successful", "Account was found!");*/

        logged = true;
    }

    if (logged == true) {
        User u(response->m_username, response->m_region);
        emit Signed(u);
    }


}

bool SignIn::isLogged() {
    return logged;
};

//BUTTONS
void SignIn::on_pushButton_SignIn_clicked() {

    if (ui->lineEdit_user->text().trimmed().isEmpty() && ui->lineEdit_pass->text().trimmed().isEmpty())
    {  QMessageBox::information(this, "Login Error", "Please insert username and password");
        emit wrongInput();}
    else {

        auto &dbRef = MovieDatabase::instance();

        auto response = dbRef.login(ui->lineEdit_user->text().toStdString(), ui->lineEdit_pass->text().toStdString());


        verifyExistingUser();

        if (response == nullptr) {

            emit AccountNotFound();
        } else {
            /*this->found = new User(response->m_username, response->m_region);
            auto wrapperParent = qobject_cast<Wrapper*>(parent());
            wrapperParent->setLoggedInUser(new User(*found));
            emit AccountFound(*found); THIS CODE DISTURBS!*/
            this->current_user = std::move(response);
        }

    }
    ui->lineEdit_pass->clear();
    ui->lineEdit_user->clear();
}

void SignIn::on_searchDemo_clicked() {
    MoviesTable moviesTable(this);
    moviesTable.setModal(true);
    moviesTable.exec();
}

void SignIn::on_pushButton_back_clicked() {
    emit HomeClicked();

}

//DESTRUCTOR
SignIn::~SignIn() {
    delete ui;
}
