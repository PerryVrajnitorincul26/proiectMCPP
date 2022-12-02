#ifndef WRAPPER_H
#define WRAPPER_H

#include <QWidget>
#include "SignUp.h"
#include "moviestable.h"

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


private:
    Ui::Wrapper *ui;
    SignUp _dialog;
    MoviesTable _moviestable;
};

#endif // WRAPPER_H
