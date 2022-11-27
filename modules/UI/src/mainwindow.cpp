#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include "dialog.h"
#include "db_headers.h"
#include "MovieDatabase.h"
#include <QHBoxLayout>
#include "moviestable.h"


MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_SignIn_clicked()
{
    auto &dbRef = MovieDatabase::instance();
    auto response = dbRef.login(ui->lineEdit_user->text().toStdString(),ui->lineEdit_pass->text().toStdString());

    verifyInputFields();
    verifyExistingUser();

    if(response == nullptr) {
        auto tempDialog = new QDialog();
        auto myDialog = new Dialog();
        auto myLayout = new QHBoxLayout();
        tempDialog->setLayout(myLayout);
        myLayout->addWidget(myDialog);
        tempDialog->exec();
    }

//    MoviesTable moviesTable(this);
//    moviesTable.setModal(true);
//    moviesTable.exec();
}

void MainWindow::verifyInputFields() {
    if(ui->lineEdit_user->text().toStdString().empty() && ui->lineEdit_pass->text().toStdString().empty())
        QMessageBox::information(this, "Login Error", "Please insert username and password");
    else if(ui->lineEdit_user->text().toStdString().empty())
        QMessageBox::information(this, "Login Error", "Please insert username");
    else if(ui->lineEdit_pass->text().toStdString().empty())
        QMessageBox::information(this, "Login Error", "Please insert password");
}

void MainWindow::verifyExistingUser() {
    auto &dbRef = MovieDatabase::instance();
    auto response = dbRef.login(ui->lineEdit_user->text().toStdString(),ui->lineEdit_pass->text().toStdString());

    if(response == nullptr)
        QMessageBox::information(this, "Login Error", "Account not found - create one!");
    else QMessageBox::information(this, "Login successful", "Account was found!");
}
