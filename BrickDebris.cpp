#include "BrickDebris.h"

BrickDebris::BrickDebris(QPointF position, Direction _dir) : Entity()
{
	//textures
	texture = Sprites::instance()->get("brick_debris");

	//set class variables
	moving = true;
	collidable = false;
	falling = false;
	jumping_duration = 20;
	dir = _dir;


	startJumping();

	//set starting pixmap, position, Z value
	setPixmap(texture);
	setPos(position);
	setZValue(4);	
}
