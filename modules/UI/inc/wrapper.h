#ifndef WRAPPER_H
#define WRAPPER_H

#include <QWidget>
#include "dialog.h"
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


private:
    Ui::Wrapper *ui;
    Dialog _dialog;
    MoviesTable _moviestable;
};

#endif // WRAPPER_H
