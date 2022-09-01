#pragma once

#include "Enemy.h"
#include "Entity.h"

class Hit_pixmap : public Entity
{
protected:

	QPixmap texture[4];

	int counter;

public:

	Hit_pixmap(int posX, int posY);
	virtual std::string name() { return "Hit pixmap"; }
	virtual void advance();
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir) {}
};