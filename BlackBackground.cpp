#include "BlackBackgroud.h"

BlackBackground::BlackBackground(QPoint position, int type)
{
	texture_black[0] = Sprites::instance()->get("black-0");
	texture_black[1] = Sprites::instance()->get("black-1");
	texture_black[3] = Sprites::instance()->get("black-2");
	texture_black[4] = Sprites::instance()->get("black-3");
	texture_black[5] = Sprites::instance()->get("black-4");
	texture_black[6] = Sprites::instance()->get("black-5");
	texture_black[7] = Sprites::instance()->get("black-6");
	texture_black[8] = Sprites::instance()->get("black-7");
	texture_black[9] = Sprites::instance()->get("black-8");

	collidable = false;
	falling = false;
	moving = false;

	setPixmap(texture_black[type]);
	setPos(position);
}

void BlackBackground::animate()
{

}

void BlackBackground::hit(Object* what, Direction fromDir)
{

}