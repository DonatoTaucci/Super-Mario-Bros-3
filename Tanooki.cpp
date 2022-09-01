#include "Tanooki.h"
#include "Point.h"

Tanooki::Tanooki(QPoint position) : Collectable(position)
{
	//textures
	tanooki = Sprites::instance()->get("tanooki");

	//set flags
	slow = false;
	collidable = false;
	moving = true;
	falling = false;

	//set counter	
	moving_div_counter = 5;
	death_duration = 0;
	counter = 0;

	//set other class variable
	moving_speed = 1;
	falling_speed = 1;
	dir = UP;

	//set staring pixmap, position and Z value
	setPos(position);
	setPixmap(tanooki);
	setZValue(4);
}

void Tanooki::animate()
{
	Entity::animate();

	if (y() == spawned_position.y() - 1 * (pixmap().height()))
	{
		slow = false;
		moving = true;
		collidable = true;
		falling = true;
		falling_speed = 2;
		dir = RIGHT;
	}
}

void Tanooki::advance()
{
	counter++;

	if (!falling && !jumping && counter >= 50)
		startJumping();

	Collectable::advance();
}


void Tanooki::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	// if hit by Mario, Mario eats mushroom and mushroom dies
	Mario* mario = dynamic_cast<Mario*>(what);
	Inert* inert = dynamic_cast<Inert*>(what);
	if (mario)
	{
		mario->powerUpTanooki();
		die();
		new Point(x(), y(), 1000);
		return;
	}
	if (fromDir == RIGHT || fromDir == LEFT)
		setDirection(inverse(dir));
}
