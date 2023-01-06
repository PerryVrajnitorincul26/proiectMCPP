#ifndef USERMENIU_H
#define USERMENIU_H

#include <QWidget>
#include "MoviesTable.h"

namespace Ui {
class UserMeniu;
}

class UserMeniu : public QWidget
{
    Q_OBJECT

public:
    explicit UserMeniu(QWidget *parent = nullptr);
    ~UserMeniu();

private:
    Ui::UserMeniu *ui;
    MoviesTable _movies;

private slots:
    void on_pushButton_LogOut_clicked();
    void on_pushButton_showMovieList_clicked();
    void on_backHome();
    void on_pushButton_sett_clicked();
    void on_pushButton_recom_clicked();
signals:
    void logout();

};

#endif // USERMENIU_H
