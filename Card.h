#pragma once

#include "Entity.h"


class Card : public Entity{
protected:

	QPixmap block[3];
	QPixmap mushroom[3];
	QPixmap star[3];
	QPixmap flower[3];

	bool hitted;

	int selected_card;			//0 = star
								//1 = flower
								//2 = mushroom

public:
	Card(QPoint position);

	virtual std::string name() { return "Card"; }

	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
	virtual void advance();
};