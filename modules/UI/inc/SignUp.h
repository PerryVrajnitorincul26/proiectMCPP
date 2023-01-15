#pragma once

#include <QWidget>
#include <regex>



namespace Ui {
    class SignUp;
}

class SignUp : public QWidget {
Q_OBJECT

    Ui::SignUp *ui;

public:
    explicit SignUp(QWidget *parent = nullptr);

    ~SignUp();

private slots:

    void on_pushButton_SignUp_clicked();

    void on_pushButton_home_clicked();

signals:

    void HomeClicked();

    void SignUpClicked();

    void noCredential();

    void usedSymbols();
};

