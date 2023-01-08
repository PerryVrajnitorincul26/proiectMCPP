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
    void on_settingsBackButt_clicked();
    void on_deleteButton_clicked();
    void on_recomBackButt_clicled();
signals:
    void logout();
    void deleteAcc();
    void backHome();

};

#endif // USERMENIU_H
