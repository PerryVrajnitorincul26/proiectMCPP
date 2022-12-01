#ifndef DIALOG_H
#define DIALOG_H

#include <QWidget>


namespace Ui {
class Dialog;
}

class Dialog : public QWidget
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:

   void on_pushButton_SignUp_clicked();
   void on_pushButton_home_clicked();

private:
    Ui::Dialog *ui;

signals:

    void HomeClicked();
};

#endif // DIALOG_H
