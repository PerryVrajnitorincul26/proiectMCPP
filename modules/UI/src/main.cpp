#include "Wrapper.h"
#include <QApplication>
#include <QFile>
#include <QTextStream>
int main(int argc, char *argv[])
{
    qputenv("QT_MESSAGELOGCONTEXT", "1");
    QApplication a(argc, argv);
    QFile styleSheetFile("SyNet.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet=QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);
    QByteArray data;
    data.append("param1=hello");
    data.append("&");
    data.append("param2=foo");
    Wrapper w;
    w.show();
    return a.exec();
}
