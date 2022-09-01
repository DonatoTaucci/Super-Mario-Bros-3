#pragma once

#include "Fire_chomper.h"	
#include "Entity.h"


class Explosion_star : public Entity
{
protected:

	QPixmap texture_star[4];

	QPoint pos;

	int number;
	int counter;
	int dirX;
	int dirY;
	int moving_counter; 

public:
	Explosion_star(QPoint position, int _number, int _dirX, int _dirY, int _counter);

	virtual std::string name() { return "Explosion_Star"; }

	virtual void advance();
	virtual void animate();
	virtual void hit(Object* what, Direction Fromdir) {}
	virtual void hurt() {}
};