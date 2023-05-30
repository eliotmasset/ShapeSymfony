#ifndef RUNGRAPHICSWIEW_H
#define RUNGRAPHICSWIEW_H

#include <QGraphicsView>
#include <QMainWindow>

class RunGraphicsView: public QGraphicsView
{
    Q_OBJECT

public:
    RunGraphicsView(QWidget *parent = nullptr);
    ~RunGraphicsView();
    void setObjectName(QAnyStringView);
    void init();

private:
    RunGraphicsView *self;
    void paintEvent(QPaintEvent *event);
    int size;
    int isDarkMode = false;
};
#endif // RUNGRAPHICSWIEW_H
