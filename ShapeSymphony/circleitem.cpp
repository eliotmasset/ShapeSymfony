#include "circleitem.h"

CircleItem::CircleItem()
{
    this->x = 2;
    this->y = 1;
    this->vitesseX = 3; // 2 unit par seconde
    this->vitesseY = 2; // 1 unit par seconde
};

double CircleItem::getX() {
    return this->x;
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
