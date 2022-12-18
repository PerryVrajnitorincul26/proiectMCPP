#include "usermeniu.h"
#include "ui_usermeniu.h"
#include "Wrapper.h"

UserMeniu::UserMeniu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserMeniu)
{
    ui->setupUi(this);
    auto wrapperParent = qobject_cast<Wrapper*>(this->parent());
}

UserMeniu::~UserMeniu()
{
    delete ui;
}

void UserMeniu::on_pushButton_LogOut_clicked() {
  emit logout();

}


