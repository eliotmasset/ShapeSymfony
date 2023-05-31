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
    void drawGrid(int paddingVertical, int paddingHoryzontal);

private:
    RunGraphicsView *self;
    void paintEvent(QPaintEvent *event);
    int size;
    bool showGrid = true;
};
#endif // RUNGRAPHICSWIEW_H
