#pragma once

#include "Sprites.h"
#include "Entity.h"


class BrickDebris : public Entity
{
protected:

	QPixmap texture;

public:

	BrickDebris(QPointF position, Direction _dir);

	virtual std::string name() { return "BrickDebris"; }
	virtual void animate(){}
	virtual void hit(Object* what, Direction fromDir) {}
};
