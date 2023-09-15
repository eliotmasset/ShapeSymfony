#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include <QColor>
#include <QJsonObject>

class CircleItem
{
    public:
        CircleItem();
        int getId();
        double getX();
        double getY();
        void setX(double x);
        void setY(double y);
        void setId(int id);
        double getVitesseX();
        double getVitesseY();
        void inverseX();
        void inverseY();
        void setVitesseX(double vitesseX);
        void setVitesseY(double vitesseY);
        QColor getColor();
        void setColor(QColor color);
        QJsonObject getJSONDatas();
        static int cpt_ids;

    private:
        int id;
        double x;
        double y;
        double vitesseX;
        double vitesseY;
        QColor color;
};

#endif // CIRCLEITEM_H
