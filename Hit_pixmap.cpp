#include "Hit_pixmap.h"
#include "Sprites.h"

Hit_pixmap::Hit_pixmap(int posX, int posY)
{
	//textures
	texture[0] = Sprites::instance()->get("hit-0");
	texture[1] = Sprites::instance()->get("hit-3");
	texture[2] = Sprites::instance()->get("hit-1");
	texture[3] = Sprites::instance()->get("hit-2");

	//set flags
	collidable = false;
	falling = false;
	
	//set counter
	counter = 0;

	//set staring pixmap, position and Z value
	setPixmap(texture[0]);
	setPos(QPoint(posX, posY));
	setZValue(4);
}

void Hit_pixmap::animate()
{
	setPixmap(texture[(counter / 3) % 4]);
}

void Hit_pixmap::advance()
{
	counter++;
	if (counter == 12)
		die();
}