#ifndef RUNGRAPHICSWIEW_H
#define RUNGRAPHICSWIEW_H

#include "circleitem.h"
#include <QGraphicsView>
#include <QMainWindow>
#include <QLineEdit>
#include <QTimer>

class RunGraphicsView: public QGraphicsView
{
    Q_OBJECT

public:
    RunGraphicsView(QWidget *parent = nullptr);
    ~RunGraphicsView();
    void setObjectName(QAnyStringView);
    void setShowGrid(bool showGrid = true);
    bool eventFilter(QObject *watched, QEvent *event);
    std::vector <CircleItem> getCircle();

public slots:
    void advance();

private:
    std::vector <CircleItem> VCircleItems;
    RunGraphicsView *self;
    void paintEvent(QPaintEvent *event);
    int size;
    int paddingVertical;
    int paddingHorizontal;
    QPen squarePen, gridPen, circlePen;
    bool showGrid = true;
    bool ctrlPress = false;
    QTimer *timer;
    QLineEdit* tooltipPosition;
    void init();
    void drawGrid(QPainter *painter);
    void setMouseTooltip(QGraphicsSceneMouseEvent *event);
    QPointF getPosMouseInRun(QPointF position);
    QPointF getPosInRun(QPointF position);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
signals:
    void circleAdded();
};
#endif // RUNGRAPHICSWIEW_H
