#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QtAwesome.h"

#include <QPropertyAnimation>

using namespace fa;

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
    connect(ui->slidingPanelToggleButton, SIGNAL(clicked()), this, SLOT(toggleSlidingPanel()));
    ui->run_graphics_view->setShowGrid(false);

    // icons :
    QtAwesome* awesome = new QtAwesome(qApp);
    awesome->initFontAwesome();

    ui->simple_mode_button->setIcon(awesome->icon("arrow-pointer"));
    ui->expert_mode_button->setIcon(awesome->icon("pen-to-square"));
    ui->simple_mode_button->setCheckable(true);
    ui->expert_mode_button->setCheckable(true);

    this->initTopPannel();
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


void MainWindow::clickSimpleMode() {
    ui->simple_mode_button->setChecked(true);
    ui->expert_mode_button->setChecked(false);
    ui->run_graphics_view->setShowGrid(false);
}

void MainWindow::clickExpertMode(){
    ui->simple_mode_button->setChecked(false);
    ui->expert_mode_button->setChecked(true);
    ui->run_graphics_view->setShowGrid(true);
}

void MainWindow::initTopPannel() {
    ui->simple_mode_button->setChecked(true);
    connect(ui->simple_mode_button, SIGNAL(clicked()), this, SLOT(clickSimpleMode()));
    connect(ui->expert_mode_button, SIGNAL(clicked()), this, SLOT(clickExpertMode()));
}

