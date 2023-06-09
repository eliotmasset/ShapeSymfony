#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include <QGraphicsEllipseItem>

class CircleItem : public QGraphicsEllipseItem
{
public:
    CircleItem();
    CircleItem(const CircleItem&);
    int getX();
    int getY();
private:
    int x;
    int y;
};

#endif // CIRCLEITEM_H
