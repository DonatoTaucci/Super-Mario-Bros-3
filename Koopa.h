#pragma once

#include "Enemy.h"


class Koopa : public Enemy
{
protected:

	QPixmap texture_walk[2];		
	QPixmap texture_smashed;		
	QPixmap texture_roll[3];
	QPixmap texture_awaking[2];

	bool hitted;
	bool roll;
	bool winged;
	bool picked_up;						//true if is currently picked up
	bool check;							//true if is picked up
	bool thrown_away;					//true if was picked up and thrown away
	bool reverse_texture;

	int animation_div;
	int smashed_counter;
	int invu_counter;
	int counter;

public:

	Koopa(QPoint position, bool _winged = false, Direction direction = LEFT);

	virtual std::string name() { return "Koopa"; }

	virtual void advance();
	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
	virtual void hurt();
	virtual void solveCollisions();

	QPainterPath shape() const;

	//setters
	void setPickedUp(bool _picked_up) { picked_up = _picked_up; }

	//getters
	bool getHitted() { return hitted; }
	bool getRoll() { return roll; }
	Direction getDirection() { return dir; }
	bool getWing() { return winged; }
	bool getPickedUp() { return picked_up; }
	bool getThrownAway() { return thrown_away; }				//used in Entity.cpp : controls  
																//that koopa ignore mario if returns true
};