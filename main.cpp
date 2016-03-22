#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setStyle("macintosh");
    MainWindow w;
    w.setWindowTitle("Picture Processing");

    w.show();

    return a.exec();
}
