#include "circleitem.h"

CircleItem::CircleItem()
{
    this->x = 1;
    this->y = 1;
};

CircleItem::CircleItem(const CircleItem&) {
    this->x = 1;
    this->y = 1;
}

int CircleItem::getX() {
    return this->x;
}

int CircleItem::getY() {
    return this->y;
}
