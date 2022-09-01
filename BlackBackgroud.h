#pragma once

#include "Entity.h"
#include "Sprites.h"

class BlackBackground : public Entity
{
private:
	QPixmap texture_black[10];

public:
	BlackBackground(QPoint position, int type);

	// inherited methods
	virtual std::string name() { return "BlackBackground"; }
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
};