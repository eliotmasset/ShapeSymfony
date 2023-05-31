#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QTime>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile styleSheetFile("./DarkTheme.qrc.depends");
    styleSheetFile.open(QFile::ReadOnly);
    a.setStyleSheet(styleSheetFile.readAll());

    MainWindow w;
    w.show();
    return a.exec();
}
