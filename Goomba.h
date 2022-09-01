#pragma once

#include "Enemy.h"
#include "Mario.h"



class Goomba : public Enemy
{
	protected:

		QPixmap texture_winged_walk[4];
		QPixmap texture_walk[2];
		QPixmap texture_smashed;

		bool winged;
		bool reverse_texture;
		bool slow_wing;								//set to slow the movement of the wings
		bool fast_wing;								//set to fast the movement of the wings
		bool death_flag;
		bool check;

		int flyng_counter;

	public:

		Goomba(QPoint position, bool isWinged = false, Direction direction = LEFT);

		virtual std::string name() {return "Goomba";}
		virtual void animate();
		virtual void hit(Object *what, Direction fromDir);
		virtual void hurt();
		virtual void advance();
		virtual void solveCollisions();

		//getter
		bool getWing() { return winged; }						
		bool getSlow() { return slow_wing; }					
		bool getFast() { return fast_wing; }					
		bool getFalling() { return falling; }				

};