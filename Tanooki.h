#pragma once

#include "Entity.h"
#include "Collectable.h"
#include "Sprites.h"
#include "Mario.h"
#include "Game.h"

class Tanooki : public Collectable
{
protected:

	QPixmap tanooki;

	int counter;

public:
	Tanooki(QPoint position);

	virtual std::string name() { return "Tanooki"; }

	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir);
};