#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void toggleSlidingPanel();
    void getActiveInstrument(QAbstractButton* button);
    void getActiveNote(QAbstractButton* button);

private:
    void init();

    Ui::MainWindow *ui;
    QButtonGroup *groupInstruments;
    QButtonGroup *groupNotes;
    QPropertyAnimation *panelAnimation;
};

#endif // MAINWINDOW_H
