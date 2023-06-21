#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "circleitem.h"
#include "qlistwidget.h"
#include <QMainWindow>
#include <QButtonGroup>
#include <QPropertyAnimation>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void handleListWidgetItemClicked(QListWidgetItem *item);

private slots:
    void toggleSlidingPanel();
    void clickSimpleMode();
    void clickExpertMode();
    void getActiveInstrument(QAbstractButton* button);
    void getActiveNote(QAbstractButton* button);

private:
    void init();

    Ui::MainWindow *ui;
    QButtonGroup *groupInstruments;
    QButtonGroup *groupNotes;
    QPropertyAnimation *panelAnimation;
    void initTopPannel();
    void updateCircleListWidget();
};


#endif // MAINWINDOW_H
