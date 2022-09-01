#pragma once

#include "Collectable.h"

class Mushroom : public Collectable
{
protected:

	int moving_speed_div;
	bool red;

public:

	Mushroom(QPoint position, bool _red = true);

	virtual std::string name() { return "Mushroom"; }
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
};