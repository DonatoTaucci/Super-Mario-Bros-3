#pragma once

#include "Entity.h"
#include "Sprites.h"

class StarBackground : public Entity
{
private:
	QPixmap texture_starBackground;			//secret room only

public:
	StarBackground(QPoint position);

	virtual std::string name() { return "StarBackground"; }

	virtual void animate() {}
	virtual void hit(Object* what, Direction fromDir) {}
};