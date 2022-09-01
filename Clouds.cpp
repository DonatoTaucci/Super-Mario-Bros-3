#include "Clouds.h"

Clouds::Clouds(QPoint position, int type)
{
	//textures
	texture_clouds[0] = Sprites::instance()->get("cloud-0");
	texture_clouds[1] = Sprites::instance()->get("cloud-1");

	//set class variables
	collidable = false;
	falling = false;
	moving = false;

	//set starting pixmap, position and Z value
	setPixmap(texture_clouds[type]);
	setPos(position);
	setZValue(1);
}