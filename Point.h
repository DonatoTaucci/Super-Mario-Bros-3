#pragma once

#include "Entity.h"

class Point : public Entity
{
protected:
    QPixmap texture_100;
    QPixmap texture_200;
    QPixmap texture_1000;

    int advance_counter;

public:
    Point(int posX, int posY, int point);

    virtual std::string name() { return "Point"; }

    virtual void advance();
    virtual void animate() {}
    virtual void hit(Object* what, Direction fromDir) {}
};