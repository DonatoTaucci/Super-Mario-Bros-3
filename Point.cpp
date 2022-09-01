#include "Point.h"
#include "Sprites.h"
#include "Game.h"

Point::Point(int posX, int posY, int point)
{
	//set flags
	falling = false;
	collidable = false;

	//set counter
	advance_counter = 0;

	//set starting pixmap, position and Z value
	if (point == 100)
	{
		texture_100 = Sprites::instance()->get("point-100");
		setPixmap(texture_100);

		Game::instance()->sumPoint(100);
	}

	else if (point == 200)
	{
		texture_200 = Sprites::instance()->get("point-200");
		setPixmap(texture_200);

		Game::instance()->sumPoint(200);
	}

	else if (point == 1000)
	{
		texture_1000 = Sprites::instance()->get("point-1000");
		setPixmap(texture_1000);

		Game::instance()->sumPoint(1000);
	}

	setPos(QPoint(posX, posY));
	setZValue(3);
}

void Point::advance()
{
	if (advance_counter % 2 == 0)
		setY(y() - 1);

	if (advance_counter == 35)
		die();

	advance_counter++;
}
