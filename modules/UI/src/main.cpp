#include "wrapper.h"
#include "QnetworkAcces.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_MESSAGELOGCONTEXT", "1");
    QApplication a(argc, argv);
    QnetworkAcces qnetworkAcces;
    QByteArray data;
    data.append("param1=hello");
    data.append("&");
    data.append("param2=foo");
    qnetworkAcces.post("https://postman-echo.com/post", data);
    Wrapper w;
    w.show();
    return a.exec();
}
