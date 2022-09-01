#include "Collectable.h"

Collectable::Collectable(QPoint position)
{
	// set attributes
	spawned_position = position;

	// set flags (spawn phase)
	slow = true;
	collidable = false;
	moving = true;
	dir = UP;				
	falling = false;
	moving_speed = 2;
	moving_div_counter = 1;
	falling_speed = 2;
	death_duration = 0;

	setZValue(2);
}