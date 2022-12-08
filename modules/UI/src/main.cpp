#include "Wrapper.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_MESSAGELOGCONTEXT", "1");
    QApplication a(argc, argv);
    QByteArray data;
    data.append("param1=hello");
    data.append("&");
    data.append("param2=foo");
    Wrapper w;
    w.show();
    return a.exec();
}
