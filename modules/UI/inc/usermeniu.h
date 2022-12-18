#ifndef USERMENIU_H
#define USERMENIU_H

#include <QWidget>

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

private slots:
    void on_pushButton_LogOut_clicked();
signals:
    void logout();
};

#endif // USERMENIU_H
