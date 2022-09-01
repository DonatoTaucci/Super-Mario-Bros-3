#include "Fire_chomper.h"
#include "Fire_tail.h"
#include "Explosion_star.h"
#include "Hit_pixmap.h"
#include "Koopa.h"

Fire_chomper::Fire_chomper(QPoint position)
{
	//textures
	texture_shooting[0] = Sprites::instance()->get("fire-chomper-shooting-0");
	texture_shooting[1] = Sprites::instance()->get("fire-chomper-shooting-1");
	texture_moving = Sprites::instance()->get("fire-chomper-moving");
	texture_explode[0] = texture_moving;
	texture_explode[1] = Sprites::instance()->get("fire-chomper-explode");

	//ignore all the collisions with other enemies
	special_case_2 = true;

	//set flags
	shooting = false;
	stop = false;
	up = false;
	down = false;

	//set counter
	moving_counter = 0;

	//set other class variables
	range = 192;
	death_duration = 300;
	prev_pos = 0;
	direction = 0;

	//generate the first piece of fire tail
	new Fire_tail(QPoint(position.x(), position.y()), this, 0, 3);

	//set starting pixmap, position and Z value	
	setPixmap(texture_moving);
	setPos(position);
	setZValue(3);
}

void Fire_chomper::advance()
{
	if (freezed)
		return;

	if(mario == 0)
		mario = Game::instance()->getMario();

	if ((x() < mario->x() + 2 * 16) && x() > mario->x() - 2 * 16 && ((y() > mario->y()) &&
		(y() < mario->y() + 32)) && mario->isSpinning())
		one_shooted = true;

	if (x() < mario->x())
		direction = -1;
	else
		direction = 1;

	if (!disable(range))
	{
		//the fire chomper explodes after it ends 
		//all the fire tale pieces
		if (stop && moving_counter == 180)
		{
			if ((mario->x() > x() && mario->x() < x() + 3 * 16) ||
				(mario->x() < x() && mario->x() > x() - 3 * 16))
				if ((mario->y() < y() && mario->y() > y() - 3 * 16) ||
					(mario->y() > y() && mario->y() < y() + 3 * 16))
					mario->MarioHurt();

			new Explosion_star(QPoint(x(), y()), 1, 1, -2, 1);
			new Explosion_star(QPoint(x(), y()), 2, 2, 0, 1);
			new Explosion_star(QPoint(x(), y()), 3, 1, 2, 1);
			new Explosion_star(QPoint(x(), y()), 4, -1, 2, 1);
			new Explosion_star(QPoint(x(), y()), 5, -2, 0, 1);
			new Explosion_star(QPoint(x(), y()), 6, -1, -2, 1);

			die();
		}
		
		if (shooting)
		{
			if (moving)						
				moving = false;

			if (moving_counter == 280)
			{
				shooting = false;
				moving_counter = 0;
			}
		
		}

		if (one_shooted)
			dying = true;

		if (dying)
		{
			death_counter++;
			if (prev_pos <= x())
			{
				prev_pos = x();
				setY(y() + 1);
				setX(x() - 3);
			}
			else
			{
				prev_pos = x();
				setY(y() + 1);
				setX(x() + 3);
			}

			if(death_counter == 1 && one_shooted)
				new Hit_pixmap(x(), y() - 16);

			if (death_counter > death_duration)
				die();
		}
		
		else
		{
			if (!moving && !shooting)
				moving = true;

			moving_counter++;

			move = mario->x() - x();

			if (moving)
			{
				if (move >= 0)
				{
					if (moving_counter % 3 == 0)
						setX(x() + 1);
				}
				else
				{
					if (moving_counter % 3 == 0)
						setX(x() - 1);
				}

				if (down)
				{
					//even if y() isn't lesser than mario->y()
					//go down for other 16 pixel, than start going up
					if (moving_counter % 3 == 0)
						setY(y() + 1);

					if (y() > mario->y() + 16)
						down = false;
				}
				//even if y() isn't higher than mario->y()
				//go up for other 16 pixel, than start going down
				else if (up)
				{
					if (moving_counter % 3 == 0)
						setY(y() - 1);

					if (y() < mario->y() - 16)
						up = false;
				}
				//if both Upand Down are false, determine Up 
				//and Down by comparing y() with mario->y()
				//and start going up or down
				else if (y() < mario->y())
				{
					if (!down)
						down = true;

					if (moving_counter % 3 == 0)
						setY(y() + 1);
				}

				else if (y() > mario->y())
				{
					if (!up)
						up = true;
					if (moving_counter % 3 == 0)
						setY(y() - 1);
				}
			}

			if (moving_counter == 250 && !stop)
			{
				shooting = true;

				//create a different Fire_ball object based on the mario's X and Y
				if (x() > mario->x() && y() > mario->y())
					new fire_ball(QPoint(x(), y()), mario, LEFT, UP, false, true);
				else if (x() < mario->x() && y() > mario->y())
					new fire_ball(QPoint(x(), y()), mario, RIGHT, UP, false, true);
				else if (x() > mario->x() && y() < mario->y())
					new fire_ball(QPoint(x(), y()), mario, LEFT, DOWN, true, true);
				else if (x() < mario->x() && y() < mario->y())
					new fire_ball(QPoint(x(), y()), mario, RIGHT, DOWN, true, true);
			}
		}
	}		
}

void Fire_chomper::animate()
{
	if (freezed)
		return;

	if (dying)
		setPixmap(texture_shooting[0].transformed(QTransform().scale(1, -1)));

	else if (moving)
	{
		if (stop && moving_counter >= 100)
			setPixmap(texture_explode[(moving_counter / 6) % 2]);
		else
			setPixmap(texture_moving);
	}
		
	else if (shooting)
	{
		if (moving_counter > 250 && moving_counter < 265)
			setPixmap(texture_shooting[0]);
		else
			setPixmap(texture_shooting[1]);	
	}

	if (direction == -1)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
	else
		direction = 1;		
}

void Fire_chomper::hit(Object* what, Direction Fromdir)
{
	Object::hit(what, Fromdir);

	if (mario && Fromdir == UP)
		Sounds::instance()->play("stomp");		
}

void Fire_chomper::hurt()
{
	dying = true;
	shooting = false;
	collidable = false;	
}

