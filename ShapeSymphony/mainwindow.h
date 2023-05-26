#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

private:
    Ui::MainWindow *ui;
    QPropertyAnimation *panelAnimation;

    void init();
};

#endif // MAINWINDOW_H
