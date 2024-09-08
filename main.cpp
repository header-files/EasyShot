#include "mainwindow.h"
#include "shotcut.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    ShotCut shotCut;
    shotCut.show();
    return a.exec();
}
