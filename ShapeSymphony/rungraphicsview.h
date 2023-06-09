#ifndef RUNGRAPHICSWIEW_H
#define RUNGRAPHICSWIEW_H

#include <QGraphicsView>
#include <QMainWindow>
#include <QLineEdit>

class RunGraphicsView: public QGraphicsView
{
    Q_OBJECT

public:
    RunGraphicsView(QWidget *parent = nullptr);
    ~RunGraphicsView();
    void setObjectName(QAnyStringView);
    void setShowGrid(bool showGrid = true);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    RunGraphicsView *self;
    void paintEvent(QPaintEvent *event);
    int size;
    int paddingVertical;
    int paddingHorizontal;
    QPen squarePen, gridPen, circlePen;
    bool showGrid = true;
    bool ctrlPress = false;
    QLineEdit* tooltipPosition;
    void init();
    void drawGrid(QPainter *painter);
    void setMouseTooltip(QGraphicsSceneMouseEvent *event);
    QPointF getPosMouseInRun(QPointF position);
    QPointF getPosInRun(QPointF position);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // RUNGRAPHICSWIEW_H
