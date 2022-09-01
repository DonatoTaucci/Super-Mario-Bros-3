#pragma once

#include "Background.h"
#include "Mario.h"


class Hud : public Background
{
	protected:
		//for each element of this vector corresponds a texture that represents the number
		std::string vector[10] = { "number-0", "number-1", "number-2", "number-3", "number-4", 
								"number-5", "number-6", "number-7", "number-8", "number-9" };

		Mario* mario_h;

		bool max_speed;

		int coinI, coinJ;
		int lifeI, lifeJ;
		int max_speed_counter;
		int point1, point2, point3, point4, point5, point6, point7;
		int card_hud[3];
		int time1, time2, time3;
		int animation_counter;
		int speed;

	public:

		Hud(const QPoint & position);

		virtual std::string name() { return "Hud"; }
		virtual void animate();

		//setters
		void setCoin(int _coinI, int _coinJ) { coinI = _coinI; coinJ = _coinJ; }
		void setLife(int _lifei, int _lifej) { lifeI = _lifei; lifeJ = _lifej; }
		void SetPointIndex(int _1, int _2, int _3, int _4, int _5, int _6, int _7);
		void setCard(int _card);
		void setMaxSpeed(bool _max_speed) { max_speed = _max_speed; }
		void setSpeed(int _speed) { speed = _speed; }
		
		//getters
		int getCoinI() { return coinI; }
		int getCoinJ() { return coinJ; }
		int getLifeI() { return lifeI; }
		int getLifeJ() { return lifeJ; }
		int getPoint1() { return point1; }
		int getPoint2() { return point2; }
		int getPoint3() { return point3; }
		int getPoint4() { return point4; }
		int getPoint5() { return point5; }
		int getPoint6() { return point6; }
		int getPoint7() { return point7; }

		
};
