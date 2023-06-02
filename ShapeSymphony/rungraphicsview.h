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
    void init();
    void drawGrid(int paddingVertical, int paddingHoryzontal);
    void setShowGrid(bool showGrid = true);
    bool eventFilter(QObject *watched, QEvent *event);

private:
    RunGraphicsView *self;
    void paintEvent(QPaintEvent *event);
    int size;
    bool showGrid = true;
    bool ctrlPress = false;
    QLineEdit* tooltipPosition;
    void setMouseTooltip(QGraphicsSceneMouseEvent *event);
    QPointF getPosMouseInRun(QPointF position);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
};
#endif // RUNGRAPHICSWIEW_H
