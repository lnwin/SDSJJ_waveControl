#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    qRegisterMetaType<QTextCursor>("QTextCursor");
    qRegisterMetaType<QList<double>>("QList<double>");
    qRegisterMetaType<QList<QString>>("QList<QString>");


    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
