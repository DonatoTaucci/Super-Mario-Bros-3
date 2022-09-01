#pragma once

#include "Enemy.h"
#include "Fire_ball.h"

class Fire_chomper : public Enemy
{
protected:

	QPixmap texture_shooting[2];
	QPixmap texture_moving;
	QPixmap texture_explode[2];

	bool shooting;
	bool stop;							//bocame true when all the Fire_tail pieces have been detached
	bool up;
	bool down;

	int move;							//move the fire chomper left or right
	int moving_counter;
	int prev_pos;
	int direction;

public:

	Fire_chomper(QPoint position);

	virtual std::string name() { return "Fire_chomper"; }

	virtual void advance();
	virtual void animate();

	virtual void hit(Object* what, Direction Fromdir);
	virtual void hurt();

	//setters and getters
	void setStop(bool _stop) { stop = _stop; }
	bool getShooting() { return shooting; }
	int getDirection() { return direction; }
	
};