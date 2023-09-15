#include "circleitem.h"

#include <QJsonObject>

int CircleItem::cpt_ids = 0;

CircleItem::CircleItem()
{
    this->x = 2;
    this->y = 1;
    this->vitesseX = 3; // 2 unit par seconde
    this->vitesseY = 2; // 1 unit par seconde
    CircleItem::cpt_ids++;
    this->id = cpt_ids;
};

double CircleItem::getX() {
    return this->x;
}

int CircleItem::getId() {
    return this->id;
}

double CircleItem::getY() {
    return this->y;
}

void CircleItem::setX(double x) {
    this->x=x;
}

void CircleItem::setY(double y) {
    this->y=y;
}

void CircleItem::setId(int id) {
    this->id=id;
}

double CircleItem::getVitesseX() {
    return this->vitesseX;
}

double CircleItem::getVitesseY() {
    return this->vitesseY;
}

void CircleItem::setVitesseX(double vitesseX) {
    this->vitesseX=vitesseX;
}

void CircleItem::setVitesseY(double vitesseY) {
    this->vitesseY=vitesseY;
}

void CircleItem::inverseX() {
    this->vitesseX=-this->vitesseX;
}

void CircleItem::inverseY() {
    this->vitesseY=-this->vitesseY;
}

QColor CircleItem::getColor() {
    return this->color;
}

void CircleItem::setColor(QColor color) {
    this->color = color;
}

QJsonObject CircleItem::getJSONDatas()
{
    QJsonObject circle;
    circle["x"] = this->x;
    circle["y"] = this->y;
    circle["vitesseX"] = this->vitesseX;
    circle["vitesseY"] = this->vitesseY;
    circle["color"] = this->color.name();
    return circle;
}
