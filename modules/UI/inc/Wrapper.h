#ifndef WRAPPER_H
#define WRAPPER_H

#include <QWidget>
#include "SignUp.h"
#include "SignIn.h"
#include "MoviesTable.h"

namespace Ui {
class Wrapper;
}

class Wrapper : public QWidget
{
    Q_OBJECT

public:
    explicit Wrapper(QWidget *parent = nullptr);
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


private:
    Ui::Wrapper *ui;
    SignUp _dialog;
    MoviesTable _moviestable;
    SignIn _signin;
};

#endif // WRAPPER_H
