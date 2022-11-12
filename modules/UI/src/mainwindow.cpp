#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "QMessageBox"
#include "dialog.h"
MainWindow::MainWindow(QWidget *parent)
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
    QString label_user=ui->lineEdit_user->text();
    QString label_password=ui->lineEdit_pass->text();
    if(label_user=="a"&& label_password=="b")
        QMessageBox::information(this,"Login","user and pass good");
    else
    {
       Dialog dialog;
       dialog.setModal(true);
       dialog.exec();
    }
}

