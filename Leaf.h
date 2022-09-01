#pragma once

#include "Entity.h"
#include "Collectable.h"
#include "Sprites.h"
#include "Mario.h"
#include "Game.h"

class Leaf : public Collectable
{
protected:

	QPixmap leaf;
	
	bool start;

	int posX;
	int posY;
	int advance_counter;

public:
	
	Leaf(QPoint position);

	virtual std::string name() { return "Leaf"; }

	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
};