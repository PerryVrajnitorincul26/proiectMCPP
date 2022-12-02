#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>


namespace Ui {
class SignUp;
}

class SignUp : public QWidget
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:

   void on_pushButton_SignUp_clicked();
   void on_pushButton_home_clicked();

private:
    Ui::SignUp *ui;

signals:

    void HomeClicked();
};

#endif // DIALOG_H
