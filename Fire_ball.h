#pragma once

#include "Entity.h"
#include "Plant.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Mario.h"


class fire_ball : public Entity
{
protected:

	QPixmap texture_fire_ball[4];
	QPixmap texture_flame[2];

	Mario* mario_f;

	Direction direction;

	bool _upsidedown;
	bool shooted_by_chomper;	

	int counter;
	int pX;						//it's used to set the fire ball direction(left or right)
	int pY;						//it's used to set the fire ball direction(up or down)

	float advanceX;				//it's used to move the fire ball to the X direction
	float advanceY;				//it's used to move the fire ball to the Y direction
	float posX;
	float posY;

public:

	fire_ball(QPoint position, Mario* mario, Direction DIRH, Direction DIRV, bool upsidedown, bool _type = false);

	virtual std::string name() { return "fire_ball"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir);


	void trajectory();
};