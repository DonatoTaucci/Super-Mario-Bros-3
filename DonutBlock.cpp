#include "DonutBlock.h"


DonutBlock::DonutBlock(QPoint position, Mario* mario) : Inert()
{
	// textures
	texture_shake[0] = Sprites::instance()->get("shake-0");
	texture_shake[1] = Sprites::instance()->get("shake-1");
	texture_shake[2] = Sprites::instance()->get("shake-2");
	texture_shake[3] = Sprites::instance()->get("shake-3");
	texture_DonutBlock = Sprites::instance()->get("donut-block");

	//set pointers
	mario_d = mario;

	//set flags
	touched = false;
	freezed = false;

	//set counters
	touch_counter = -60;
	animation_counter = 0;

	//set other class variables
	posX = position.x();
	posY = position.y();


	//set starting pixmap, position, Z value
	setPixmap(texture_DonutBlock);
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(3);
}

void DonutBlock::advance()
{
	if (freezed)
		return;

	if (!mario_d->isBig())
	{
		if (mario_d->x() > posX - 8 && mario_d->x() < posX + 8 && mario_d->y() > posY - 33)
			touched = true;
		else
			touched = false;
	}
	else if (mario_d->isBig())
	{
		if (mario_d->x() > posX - 8 && mario_d->x() < posX + 8 && mario_d->y() > posY -49 )
			touched = true;
		else
			touched = false;
	}

	if (touch_counter < 0)
	{
		if (touched)
			touch_counter++;
		else
			touch_counter = -60;
	}

	if (touch_counter == 0 )			
		setY(y() + 1);							//if the touch_counter reaches 0 the donut
												//block starts falling and wont stop
}

void DonutBlock::animate()
{
	if (freezed)
		return;

	animation_counter++;

	if (touched)
		setPixmap(texture_shake[(animation_counter) % 4]);
	else
		setPixmap(texture_DonutBlock);

}

void DonutBlock:: hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);
}

//a new shape is created to avoid crashes and bugs
QPainterPath DonutBlock::shape() const
{
	QPainterPath path;
	path.addRect(16, 16, -16, -16);
	return path;
}

