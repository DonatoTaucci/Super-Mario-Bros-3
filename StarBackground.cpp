#include"StarBackground.h"

StarBackground::StarBackground(QPoint position)
{
	//textures
	texture_starBackground = Sprites::instance()->get("StarBackground");

	//set flags
	collidable = false;
	falling = false;
	moving = false;

	//set starting pixmap and position
	setPixmap(texture_starBackground);
	setPos(position);
}
