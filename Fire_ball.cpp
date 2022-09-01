#include "Fire_ball.h"

fire_ball::fire_ball(QPoint position, Mario* mario, Direction DIRH, Direction DIRV, bool upsidedown, bool _type)
{
	//textures
	texture_fire_ball[0] = Sprites::instance()->get("fire-ball-0");
	texture_fire_ball[1] = Sprites::instance()->get("fire-ball-1");
	texture_fire_ball[2] = Sprites::instance()->get("fire-ball-2");
	texture_fire_ball[3] = Sprites::instance()->get("fire-ball-3");
	texture_flame[0] = Sprites::instance()->get("flame");
	texture_flame[1] = texture_flame[0].transformed(QTransform().scale(-1, 1));

	//set pointer
	mario_f = mario;

	//ignore all the collisions with other enemies
	special_case_2 = true;

	//set counter
	counter = 0;

	//set other class variables
	_upsidedown = upsidedown;
	posX = position.x();
	posY = position.y();
	shooted_by_chomper = _type;						//type = false -> plant	
													//type = true  -> fire chomper
	if (shooted_by_chomper)
		direction = DIRH;

	//the values ​​of pY and pX are determined on the values of DIRH and DIRV
	if (DIRH == LEFT && DIRV == DOWN)
	{
		pX = -1;
		pY = 1;
	}
	else if (DIRH == RIGHT && DIRV == DOWN)
	{
		pX = 1;
		pY = 1;
	}
	else if (DIRH == RIGHT && DIRV == UP)
	{
		pX = 1;
		pY = -1;
	}
	else if (DIRH == LEFT && DIRV == UP)
	{
		pX = -1;
		pY = -1;
	}

	//set starting pixmap
	if (!shooted_by_chomper)
		setPixmap(texture_fire_ball[0]);
	else
		setPixmap(texture_flame[0]);

	Sounds::instance()->play("fireball");

	//set starting position and Z value
	if (!shooted_by_chomper)
	{
		if (!_upsidedown)
			setPos(position - QPoint(0, pixmap().height() + 48));
		else
			setPos(position - QPoint(0, pixmap().height()));
	}
	else
	{
		if (upsidedown)
			setPos(position - QPoint(0, pixmap().height()));
		else
			setPos(position);
	}

	setZValue(5);
}

void fire_ball::advance()
{
	if (counter == 0)
		trajectory();

	counter++;

	setY(y() + advanceY * pY);
	setX(x() + advanceX * pX);

	if (counter >= 300)
		die();
}

void fire_ball::animate()
{

	if (!shooted_by_chomper)
		setPixmap(texture_fire_ball[(counter / 6) % 4]);
	else
	{
		if (counter % 2)
			setPixmap(texture_flame[(counter / 6) % 2]);
	}
}

void fire_ball::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	if (dynamic_cast<Mario*>(what))
	{
		if (mario_f->getInvCounter() < 0)
			mario_f->MarioHurt();
	}
	else
		return;
}

void fire_ball::trajectory()
{
	float tempx, tempy, temp;

	if (!_upsidedown)
	{
		tempx = abs(abs(mario_f->x()) - abs(posX));

		if (!shooted_by_chomper)
			tempy = abs(abs(mario_f->y()) - abs(posY - 64));	//applying an height correction for the fire plant

		else
			tempy = abs(abs(mario_f->y()) - abs(posY - 32));	//applying an height correction for the fire chomper

		temp = tempx + tempy;

		advanceX = (tempx / temp);
		advanceY = (tempy / temp);
	}

	else
	{
		tempx = abs(abs(mario_f->x()) - abs(posX));
		tempy = abs(abs(mario_f->y()) - abs(posY - 16));		//applying an height correction for the fireplant
		temp = tempx + tempy;

		advanceX = (tempx / temp);
		advanceY = (tempy / temp);
	}
}
