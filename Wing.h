#pragma once

#include "Enemy.h"
#include "Sprites.h"
#include "Entity.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopa.h"


class Wing : public Entity
{
protected:
	
	QPixmap texture_wing[2];
	
	Goomba* goomba_w;
	Koopa* koopa_w;
	
	bool reverse;
	bool slow;
	bool fast;
	bool fall;

	int animation_wing;
	int flyng_counter;

public:
	Wing(QPoint pos, Goomba* _goomba_w, Koopa* _koopa_w, bool isGoomba, bool reverse);

	virtual std::string name() { return "wing"; }

	virtual void animate();
	virtual void hit(Object* what, Direction fromDir) {}
	virtual void hurt(){}
	virtual void advance();
	virtual void solveCollisions(){}

	Wing* getThis() { return this; }
};