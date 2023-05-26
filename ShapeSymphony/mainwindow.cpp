#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPropertyAnimation>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->slidingPanel->setMaximumHeight(0);
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    panelAnimation = new QPropertyAnimation(ui->slidingPanel, "maximumHeight");
    panelAnimation->setStartValue(0);
    panelAnimation->setDuration(500);
    connect(ui->slidingPanelToggleButton, &QPushButton::clicked, this, &MainWindow::toggleSlidingPanel);
}

void MainWindow::toggleSlidingPanel()
{
    if (ui->slidingPanel->maximumHeight() == 0) {
        panelAnimation->setEndValue(200); // Replace 200 with the desired panel height
        ui->slidingPanelToggleButton->setText("▼");
    } else {
        panelAnimation->setEndValue(0);
        ui->slidingPanelToggleButton->setText("▲");
    }

    panelAnimation->start();
}


