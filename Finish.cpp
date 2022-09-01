#include "Finish.h"
#include "Sprites.h" 
#include "qpainter.h"

Finish::Finish(QPoint position, int type, int card)
{
	//textures
	texture_clear	   = Sprites::instance()->get("stage-clear");
	texture_got_a_card = Sprites::instance()->get("got-a-card");
	texture_card[0]    = Sprites::instance()->get("star-hud");
	texture_card[1]    = Sprites::instance()->get("flower-hud");
	texture_card[2]    = Sprites::instance()->get("mushroom-hud");

	//set starting pixmap, position , Z value
	setPos(position);
	if (type == 1)
		setPixmap(texture_clear);
	else if (type == 2)
		setPixmap(texture_got_a_card);
	else if (type == 3)
		setPixmap(texture_card[card]);
	setZValue(1);
}