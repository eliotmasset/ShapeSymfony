#include "rungraphicsview.h"
#include <QStyle>
#include <QPainter>
#include <QPen>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QToolTip>
#include <QCursor>
#include <QKeyEvent>
#include "circleitem.h"
#include <vector>
#include <iostream>

const int PADDING_RUN = 25;
const int NB_LINES = 8;
const int SIZE_RUN = 10;
std::vector <CircleItem> VCircleItems;

RunGraphicsView::RunGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    init();
}

RunGraphicsView::~RunGraphicsView()
{
}

void RunGraphicsView::init()
{
    QGraphicsScene *scene = new QGraphicsScene(this);

    CircleItem *circle = new CircleItem();
    VCircleItems.push_back(*circle);
    scene->addItem(circle);
    setMouseTracking(true);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorViewCenter);
    setScene(scene);
    scene->installEventFilter(this);
    tooltipPosition = new QLineEdit(this->window());
    tooltipPosition->setMouseTracking(false);
    tooltipPosition->hide();
    show();
    grabKeyboard();

    squarePen.setWidth(1);
    squarePen.setStyle(Qt::SolidLine);
    squarePen.setColor(*(new QColor(255,255,255)));


    circlePen.setWidth(2);
    circlePen.setStyle(Qt::SolidLine);
    circlePen.setColor(*(new QColor(255,0,255)));

    QList<qreal> dashes;
    dashes << 4 << 8 << 4 << 8;
    gridPen.setWidth(1);
    gridPen.setStyle(Qt::DashLine);
    gridPen.setDashPattern(dashes);
    gridPen.setColor(*(new QColor(200,200,200)));
}

QPointF RunGraphicsView::getPosInRun(QPointF position) {
    position.setX(paddingHorizontal+((position.x()*size)/SIZE_RUN));
    position.setY(paddingVertical+((position.y()*size)/SIZE_RUN));
    return position;
}

void RunGraphicsView::paintEvent(QPaintEvent *event){
    painter = new QPainter(viewport());
    painter->setRenderHint(QPainter::Antialiasing);
    bool widthGreaterThanHeight = this->width() >  this->height() ;
    size = widthGreaterThanHeight ?  this->height()-(2*PADDING_RUN) :  this->width()-(2*PADDING_RUN);
    paddingVertical = widthGreaterThanHeight ? PADDING_RUN : (this->height()-size)/2;
    paddingHorizontal = widthGreaterThanHeight ? (this->width()-size)/2 : PADDING_RUN;
    painter->setPen(squarePen);
    painter->drawRect(paddingHorizontal,paddingVertical,size,size);

    if(this->showGrid) this->drawGrid();

    painter->setPen(circlePen);
    for (unsigned i = 0; i < VCircleItems.size(); i++){
        QPointF pos = getPosInRun(QPointF(VCircleItems[i].getX(), VCircleItems[i].getY()));
        painter->drawEllipse(pos.x(), pos.y(), size/SIZE_RUN, size/SIZE_RUN);
    }

    painter->end();
    destroy(painter);
}

void RunGraphicsView::setObjectName(QAnyStringView name) {
    parent()->setObjectName(name);
}

void RunGraphicsView::drawGrid() {
    painter->setPen(gridPen);

    for (int i = 1; i <= NB_LINES+1; i++) {
        painter->drawLine(paddingHorizontal+(i*(size/SIZE_RUN)),
                         paddingVertical,
                         paddingHorizontal+(i*(size/SIZE_RUN)),
                         paddingVertical+size);
    }

    for (int i = 1; i <= NB_LINES+1; i++) {
        painter->drawLine(paddingHorizontal,
                         paddingVertical+(i*(size/SIZE_RUN)),
                         paddingHorizontal+size,
                         paddingVertical+(i*(size/SIZE_RUN)));
    }
}

void RunGraphicsView::setShowGrid(bool showgrid) {
    this->showGrid = showgrid;
    this->update();
}

QPointF RunGraphicsView::getPosMouseInRun(QPointF position) {
    if(this->ctrlPress) {
        position.setX(round(((position.x()+size/2)*SIZE_RUN/size)*10)/10);
        position.setY(round(((position.y()+size/2)*SIZE_RUN/size)*10)/10);
    } else {
        position.setX(round(((position.x()+size/2)*SIZE_RUN/size)*100)/100);
        position.setY(round(((position.y()+size/2)*SIZE_RUN/size)*100)/100);
    }
    return position;
}

void RunGraphicsView::setMouseTooltip(QGraphicsSceneMouseEvent *event) {
    const QPointF position = getPosMouseInRun(event->scenePos());
    QString pos_x = QString::number(position.x());
    QString pos_y = QString::number(position.y());
    this->tooltipPosition->setText(pos_x+";"+pos_y);
    QPoint p = event->screenPos();
    p.setX(p.x()+10);
    p.setY(p.y()-30);
    this->tooltipPosition->move(p);
    this->tooltipPosition->show();
}


bool RunGraphicsView::eventFilter(QObject *watched, QEvent *event)
{
    if(watched == this->scene()){
        // press event
        QGraphicsSceneMouseEvent *mouseSceneEvent;
        if(event->type() == QEvent::GraphicsSceneMousePress){
            mouseSceneEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
        }
        // enter event
        else if (event->type() == QEvent::GraphicsSceneHoverEnter) {
            this->tooltipPosition->show();
        }
        // leave event
        else if (event->type() == QEvent::GraphicsSceneLeave) {
            this->tooltipPosition->hide();
        }
        // move event
        else if (event->type() == QEvent::GraphicsSceneMouseMove) {
            mouseSceneEvent = static_cast<QGraphicsSceneMouseEvent *>(event);
            this->setMouseTooltip(mouseSceneEvent);
        }
    }
    return QGraphicsView::eventFilter(watched, event);
}

void RunGraphicsView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control) {
        this->ctrlPress = true;
    }
}

void RunGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control) {
        this->ctrlPress = false;
    }
}

