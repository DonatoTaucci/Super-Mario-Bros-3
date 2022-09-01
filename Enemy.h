#pragma once

#include "Entity.h"
#include "Mario.h"


class Enemy : public Entity
{
	protected:

		Mario* mario;

		bool one_shooted;				//if this flag is true, the enemy will do a 
										//different death animation and generate
										///an object of the Hit_pixmap class

		int range;						//enemy activation range
		int moving_div;
		
	public:

		Enemy();

		// pure virtual methods that must be implemented
		virtual std::string name() = 0;
		virtual void animate() = 0;
		virtual void hit(Object *what, Direction fromDir) = 0;
		virtual void hurt() = 0;

		bool disable(int range);
		void oneShooted() { one_shooted = true; }


};