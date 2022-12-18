#ifndef WRAPPER_H
#define WRAPPER_H

#include <QWidget>
#include "SignUp.h"
#include "SignIn.h"
#include "MoviesTable.h"
#include "usermeniu.h"
namespace Ui {
class Wrapper;
}

class Wrapper : public QWidget {
Q_OBJECT


public:
    explicit Wrapper(QWidget *parent = nullptr);

    User *getLoggedInUser() const;

    void setLoggedInUser(User *loggedInUser);

    ~Wrapper();


private slots:

    void on_pushButton_goSignIn_clicked();

    void on_pushButton_goSignUp_clicked();

    void on_pushButton_goMovieList_clicked();

    void on_pushButton_back_clicked();

    void moveHome();

    void showMovieList();

    void disableSignUp();

    void UpToIn();

    void InToUp();

    void toMeniu();

    void reset();


private:
    Ui::Wrapper *ui;
    SignUp _signup;
    MoviesTable _moviestable;
    SignIn _signin;
    UserMeniu _usermeniu;

    User *loggedInUser = nullptr;
};

#endif // WRAPPER_H
