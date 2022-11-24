#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include "dialog.h"
#include "db_headers.h"
#include "MovieDatabase.h"


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
    if(response == nullptr) {
        QMessageBox::information(this, "Login Error", "Account not found - create one!");
        Dialog dialog;
        dialog.setModal(true);
        dialog.exec();
    }
}
