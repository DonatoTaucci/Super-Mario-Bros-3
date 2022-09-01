#pragma once

#include "Background.h"

class Finish : public Background
{
protected:
	QPixmap texture_clear;
	QPixmap texture_got_a_card;
	QPixmap texture_card[3];

public:

	Finish(QPoint position, int type, int card = -1);

	virtual std::string name() { return "Finish"; }

	virtual void advance() {}
	virtual void animate() {}
	virtual void hit(Object* what, Direction fromDir) {}
};