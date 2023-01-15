#ifndef USERMENIU_H
#define USERMENIU_H

#include <QWidget>
#include "MoviesTable.h"
#include "MovieDatabase.h"
#include "SignIn.h"
namespace Ui {
class UserMeniu;
}

class UserMeniu : public QWidget
{
    Q_OBJECT

public:
    explicit UserMeniu(QWidget *parent = nullptr);
    ~UserMeniu();

    void setCurrentUser(User *currentUser);

private:
    Ui::UserMeniu *ui;
    MoviesTable _movies;
    SignIn _signin;
    User* currentUser;
    ShowMovie *_showMovie=nullptr;

    std::vector<std::string> userLikedGenres;



private slots:
    void on_pushButton_LogOut_clicked();
    void on_pushButton_showMovieList_clicked();
    void on_backHome();
    void on_pushButton_sett_clicked();
    void on_pushButton_recom_clicked();
    void on_settingsBackButt_clicked();
    void on_deleteButton_clicked();
    void on_backButtRec_clicked();
    void showUser();
    void on_likedGenres_pushButton_clicked();
    void on_pushButton_Wish_clicked();
    void on_pushButton_Recommended_clicked();
    void on_recBackButton_1_clicked();
signals:
    void logout();
    void deleteAcc();
    void backHome();

};

#endif // USERMENIU_H
