#include "rungraphicsview.h"
#include <QStyle>
#include <QPainter>
#include <QPen>

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
    this->show();
}

void RunGraphicsView::paintEvent(QPaintEvent *event){
    QPainter painter(viewport());
    QPen pen;
    pen.setWidth(1);
    pen.setStyle(Qt::SolidLine);
    pen.setColor(*(new QColor(255,255,255)));
    painter.setPen(pen);
    bool widthGreaterThanHeight = this->width() >  this->height() ;
    size = widthGreaterThanHeight ?  this->height()-50 :  this->width()-50;
    isDarkMode = QPalette().color(QPalette::Window);
    int paddingVertical = widthGreaterThanHeight ? 25 : (this->height()-size)/2;
    int paddingHoryzontal = widthGreaterThanHeight ? (this->width()-size)/2 : 25;
    painter.drawRect(paddingHoryzontal,paddingVertical,size,size);
}

void RunGraphicsView::setObjectName(QAnyStringView name) {
    parent()->setObjectName(name);
}
