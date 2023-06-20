#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include <QColor>

class CircleItem
{
public:
    CircleItem();
    double getX();
    double getY();
    void setX(double x);
    void setY(double y);
    double getVitesseX();
    double getVitesseY();
    void inverseX();
    void inverseY();
    void setVitesseX(double vitesseX);
    void setVitesseY(double vitesseY);
    QColor getColor();
    void setColor(QColor color);

private:
    double x;
    double y;
    double vitesseX;
    double vitesseY;
    QColor color;
};

#endif // CIRCLEITEM_H
