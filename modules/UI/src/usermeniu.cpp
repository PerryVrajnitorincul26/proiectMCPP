#include "usermeniu.h"
#include "ui_usermeniu.h"

UserMeniu::UserMeniu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserMeniu)
{
    ui->setupUi(this);
}

UserMeniu::~UserMeniu()
{
    delete ui;
}

void UserMeniu::on_pushButton_LogOut_clicked() {
  emit logout();

}


