#pragma once

#include "Entity.h"
#include "Sprites.h"

class Clouds : public Entity
{
protected:
	QPixmap texture_clouds[2];

public:
	Clouds(QPoint position, int type);

	virtual std::string name() { return "Clouds"; }
	virtual void animate() {}
	virtual void hit(Object* what, Direction fromDir) {}
};