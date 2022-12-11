#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <db_headers.h>
#include <MovieDatabase.h>
#include <User.h>
QT_BEGIN_NAMESPACE
namespace Ui { class SignIn; }
QT_END_NAMESPACE

class SignIn : public QWidget
{
    Q_OBJECT
public:
    SignIn(QWidget *parent = nullptr);
    ~SignIn();
    std::unique_ptr<user_row> current_user=nullptr;

private slots:


    void on_pushButton_SignIn_clicked();
    void on_searchDemo_clicked();
    void on_pushButton_back_clicked();


//    void showDebug();

private:
    Ui::SignIn *ui;
    bool logged=false;
public:
    bool isLogged();

private:

    void verifyInputFields();
    void verifyExistingUser();

signals:
    void HomeClicked();

};
#endif // MAINWINDOW_H
