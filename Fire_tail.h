#pragma once

#include "Fire_chomper.h"
#include "Enemy.h"


class Fire_tail : public Enemy
{
protected:

	QPixmap texture_fire_tail[4];

	Fire_chomper* fire_chomper;
	Fire_tail* fire_tail;

	bool stop;						//stop follow the fire chomper OR 
									//an other fire tail piece

	int counter;
	int stop_counter;
	int detach;						//delete the fire tail piece with the same number as detach
	int delay;						//inserts a delay to create a curvy effect
	int direction;
	int number;						//the fire tail is composed by 4 piecies
									//and every piece is identified by this number

	

public:

	Fire_tail(QPoint position, Fire_chomper* _fire_chomper, Fire_tail* _fire_tail, int _number);

	virtual std::string name() { return "Fire_tail"; }

	virtual void advance();
	virtual void animate();
	virtual void hit(Object* what, Direction Fromdir);
	virtual void hurt() {}
};