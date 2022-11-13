#include "dialog.h"
#include "ui_dialog.h"
#include "User.h"
#include "QMessageBox"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;

}



void Dialog::on_pushButton_SignUp_clicked()
{
    QString label_Region=ui->lineEdit_Region->text();
    QString label_Username=ui->lineEdit_UsernameRegister->text();
    QString label_Password=ui->lineEdit_PasswordRegister->text();
if(label_Username=='a')
QMessageBox::warning(this,"SignUp","Username already used");
if(label_Username!='a')
QMessageBox::information(this,"SignUp","Account succesfully made!");



}

