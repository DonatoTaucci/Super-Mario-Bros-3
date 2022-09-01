#include "Fire_tail.h"


Fire_tail::Fire_tail(QPoint position, Fire_chomper* _fire_chomper, Fire_tail* _fire_tail, int _number)
{
	//textures
	texture_fire_tail[0] = Sprites::instance()->get("fire-ball-0");
	texture_fire_tail[1] = Sprites::instance()->get("fire-ball-1");
	texture_fire_tail[2] = Sprites::instance()->get("fire-ball-2");
	texture_fire_tail[3] = Sprites::instance()->get("fire-ball-3");

	//set pointers
	fire_chomper = _fire_chomper;
	fire_tail = _fire_tail;

	//set counters
	counter = 0;
	stop_counter = 0;

	//set other class variables
	death_duration = 290;
	detach = -1;
	number = _number;
	stop = false;
	collidable = false;

	if (number == 3)
		delay = 3;
	else if (number == 2)
		delay = 6;
	else if (number == 1)
		delay = 9;
	else if (number == 0)
		delay = 12;

	//generate an other piece of fire tail
	if (_number > 0)
		new Fire_tail(QPoint(position.x(), position.y()), fire_chomper, this, number - 1);

	//set starting pixmap, position, Z value
	setPixmap(texture_fire_tail[number]);			//all the pieces will have a different texture
													//in a specific time
	setPos(position);
	setZValue(2);

}

void Fire_tail::advance()
{

	if (fire_chomper->isDying())
	{
		death_counter++;

		if (death_counter > death_duration)
			die();
	}

	counter++;

	direction = fire_chomper->getDirection();

	if (fire_chomper->getShooting() && dying == false)
	{
		detach++;
		stop = true;
		if (detach == 3)
			fire_chomper->setStop(true);							//fire chomper won't shoot anymore

		//detach only one piece of fire tail 
		//(the last one, which is the one eth the lowest number)
		if (number == detach)
			die();

		dying = true;												//setting dying = true is necessary to delete a single fire tail
	}
	
	else if(fire_chomper->getShooting() == false && dying == true)
		dying = false;
		
	if (stop)
	{
		stop_counter++;
		if (stop_counter == 30)
		{
			stop_counter = 0;
			stop = false;
		}
	}
	
	if (fire_tail != 0 && !stop)
	{
		//this fire tail piece is following 
		//another fire tail piece
		if (counter % delay == 0)
		{
			setX(fire_tail->x() + 4 * direction);
			setY(fire_tail->y());
		}
	}
	
	else if (!stop)
	{
		//this fire tail piece is following the fire chomper
		if (counter % delay == 0)
		{
			setX(fire_chomper->x() + 4 * direction);
			setY(fire_chomper->y());
		}
	}
}

void Fire_tail::animate()
{
	setPixmap(texture_fire_tail[((counter / 5)) % 4]);
}

void Fire_tail::hit(Object* what, Direction Fromdir)
{
	Mario* mario = dynamic_cast<Mario*>(what);

	if (mario && mario->getInvCounter() < 0)
		mario->MarioHurt();

}