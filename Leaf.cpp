#include "Leaf.h"
#include "Enemy.h"
#include "Point.h"

Leaf::Leaf(QPoint position) : Collectable(position)
{
	//textures
	leaf = Sprites::instance()->get("leaf");

	//set flags
	start = true;

	//set counter
	death_duration = 0;
	advance_counter = 0;
	moving_div_counter = 5;

	//set other class variables
	dir = UP;
	posX = position.x();
	posY = position.y();
	slow = false;
	collidable = false;
	moving = true;
	falling = false;
	moving_speed = 1;
	falling_speed = 1;
	
	//set statirng pixmap, position and Z value
	setPixmap(leaf);
	setPos(position);
	setZValue(4);
}

void Leaf::animate()
{
	Entity:: animate();

	if (dir == RIGHT)
		setPixmap(leaf.transformed(QTransform().scale(-1, 1)));
	
	else
		setPixmap(leaf);

	if (y() == posY - 4 * 16)
	{
		slow = true;
		collidable = true;
		falling = true;
		moving_speed_div = 1;
		falling_speed_div = 3;
		dir = RIGHT;
		advance_counter++;
	}

	//create a curvy movement of the leaf
	if (advance_counter > 0)
	{
		advance_counter++;
		
		if (dir == RIGHT)
		{
			if (advance_counter % 35 == 0)
				dir = LEFT;
		}
		
		else if (dir == LEFT)
		{
			if (advance_counter % 35 == 0)
				dir = RIGHT;
		}	
	}
}

void Leaf::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	// if hit by Mario, Mario pick up the leaf and the leaf dies
	Mario* mario = dynamic_cast<Mario*>(what);
	
	if (mario)
	{
		mario->powerUpLeaf();
		die();
		new Point(x(), y(), 1000);
		return;
	}
}
