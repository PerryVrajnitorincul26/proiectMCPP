#include "SignIn.h"
#include "QnetworkAcces.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QnetworkAcces qnetworkAcces;
    QByteArray data;
    data.append("param1=hello");
    data.append("&");
    data.append("param2=foo");
    qnetworkAcces.post("https://postman-echo.com/post", data);
    SignIn w;
    w.show();
    return a.exec();
}
