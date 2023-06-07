#include "rungraphicsview.h"
#include <QStyle>
#include <QPainter>
#include <QPen>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>
#include <QToolTip>
#include <QCursor>
#include <QKeyEvent>

const int PADDING_RUN = 25;
const int NB_LINES = 8;
const int SIZE_RUN = 10;

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

    this->setMouseTracking(true);
    this->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    this->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    this->setScene(scene);
    scene->installEventFilter(this);
    this->tooltipPosition = new QLineEdit(this->window());
    this->tooltipPosition->setMouseTracking(false);
    this->tooltipPosition->hide();
    this->show();
    this->grabKeyboard();
}

void RunGraphicsView::paintEvent(QPaintEvent *event){
    QPainter painter(viewport());
    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(*(new QColor(255,255,255)));
    painter.setPen(pen);
    bool widthGreaterThanHeight = this->width() >  this->height() ;
    size = widthGreaterThanHeight ?  this->height()-(2*PADDING_RUN) :  this->width()-(2*PADDING_RUN);
    int paddingVertical = widthGreaterThanHeight ? PADDING_RUN : (this->height()-size)/2;
    int paddingHoryzontal = widthGreaterThanHeight ? (this->width()-size)/2 : PADDING_RUN;
    painter.drawRect(paddingHoryzontal,paddingVertical,size,size);

    if(this->showGrid) this->drawGrid(paddingVertical, paddingHoryzontal);
}

void RunGraphicsView::setObjectName(QAnyStringView name) {
    parent()->setObjectName(name);
}

void RunGraphicsView::drawGrid(int paddingVertical, int paddingHoryzontal) {
    QPainter painter(viewport());
    QPen pen;
    QList<qreal> dashes;
    dashes << 4 << 8 << 4 << 8;
    pen.setWidth(1);
    pen.setStyle(Qt::DashLine);
    pen.setDashPattern(dashes);

    pen.setColor(*(new QColor(200,200,200)));
    painter.setPen(pen);
    painter.setRenderHint(QPainter::Antialiasing);

    for (int i = 1; i <= NB_LINES+1; i++) {
        painter.drawLine(paddingHoryzontal+(i*(size/10.0)),
                         paddingVertical,
                         paddingHoryzontal+(i*(size/10.0)),
                         paddingVertical+size);
    }

    for (int i = 1; i <= NB_LINES+1; i++) {
        painter.drawLine(paddingHoryzontal,
                         paddingVertical+(i*(size/10.0)),
                         paddingHoryzontal+size,
                         paddingVertical+(i*(size/10.0)));
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
    if((position.x() > 0 && position.x()< SIZE_RUN) && (position.y()>0 && position.y()<SIZE_RUN)){
        QString pos_x = QString::number(position.x());
        QString pos_y = QString::number(position.y());
        this->tooltipPosition->setText(pos_x+";"+pos_y);
        QPoint p = event->screenPos();
        p.setX(p.x()-125);
        p.setY(p.y()-50);
        this->tooltipPosition->move(p);
        this->tooltipPosition->show();
    } else {
        this->tooltipPosition->close();
    }
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

