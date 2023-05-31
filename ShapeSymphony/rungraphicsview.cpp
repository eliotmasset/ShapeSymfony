#include "rungraphicsview.h"
#include <QStyle>
#include <QPainter>
#include <QPen>

const int PADDING_RUN = 25;
const int NB_LINES = 8;

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
