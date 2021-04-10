#include "mainwindow.h"
#include <QApplication>
#include <QString>
#include <QDebug>

int main(int argc, char* argv[])
{
    QString arg = nullptr;

    if(argc > 1)
        arg = argv[1];

    if(arg == "--version")
    {
        qDebug() << "1.2.6";
        return 0;
    }
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon("icon.png"));
    MainWindow w(arg);
    w.show();

    return a.exec();
}
