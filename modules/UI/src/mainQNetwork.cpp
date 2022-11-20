#include <QCoreApplication>
#include "QnetworkAcces.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    QnetworkAcces qnetworkAcces;

    QByteArray data;
    data.append("param1=hello");
    data.append("&");
    data.append("param2=foo");
    qnetworkAcces.post("https://postman-echo.com/post", data);
    return a.exec();
}