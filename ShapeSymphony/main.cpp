#include "mainwindow.h"

#include <QApplication>

using namespace Qt::StringLiterals;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.show();
    return a.exec();
}
