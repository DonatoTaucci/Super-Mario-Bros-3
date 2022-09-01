#pragma once

#include "Sprites.h"
#include "Inert.h"
#include "Secret_box.h"
#include "Collectable.h"


class Brick : public Inert
{
protected:

	QPixmap texture_brick[4];
	QPixmap texture_inactive;

	spawnable_type content;

	Mario* mario_b;

	bool drop;
	bool active;
	bool broken;
	bool skip;

	int animation_counter;
	int hit_counter;
	int hit_duration;
	

public:

	Brick(QPoint position, bool _drop = false, spawnable_type _content = LEAF);

	// pure virtual methods that must be implemented
	virtual std::string name() { return "Brick"; }
	virtual void advance();
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
};