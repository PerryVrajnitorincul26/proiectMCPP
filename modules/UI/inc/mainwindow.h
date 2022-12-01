#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <db_headers.h>
#include <MovieDatabase.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::unique_ptr<user_row> current_user=nullptr;

private slots:


    void on_pushButton_SignIn_clicked();
    void on_searchDemo_clicked();


//    void showDebug();

private:
    Ui::MainWindow *ui;

    void verifyInputFields();
    void verifyExistingUser();

};
#endif // MAINWINDOW_H
