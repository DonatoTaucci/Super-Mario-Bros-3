#include "Plant.h"
#include "Hit_pixmap.h"

Plant::Plant(QPoint position, Direction direction, bool _upsidedown, bool _type)
{
	//textures
	texture_biteplant[0] = Sprites::instance()->get("biteplant-0");
	texture_biteplant[1] = Sprites::instance()->get("biteplant-1");
	texture_fireplant[0] = Sprites::instance()->get("fireplant-0");
	texture_fireplant[1] = Sprites::instance()->get("fireplant-1");
	texture_fireplant[2] = Sprites::instance()->get("fireplant-2");
	texture_fireplant[3] = Sprites::instance()->get("fireplant-3");
	texture_cloud[0] = Sprites::instance()->get("transf-cloud-0");
	texture_cloud[1] = Sprites::instance()->get("transf-cloud-1");
	texture_cloud[2] = Sprites::instance()->get("transf-cloud-2");
	texture_cloud[3] = Sprites::instance()->get("transf-cloud-3");

	//set flags
	mouth = false;
	notmove = false;
	upsidedown = _upsidedown;
	fire_plant = _type;
	if (!upsidedown)
		done = false;
	else
		done = true;

	//set counters
	pause = 0;
	advance_counter = 0;
	death_duration = 20;

	//set other class variables
	tex = 1;
	dir = direction;
	pos = position;

	//set starting pixmap, position and Z value
	setPixmap(texture_fireplant[tex]);
	setPos(position - QPoint(0, pixmap().height()));

	setZValue(2);
}

void Plant::advance()
{
	moving_div = 4;

	if (freezed)
		return;

	if (mario == 0)
		mario = Game::instance()->getMario();

	if ((x() < mario->x() + 2 * 16) && x() > mario->x() - 2 * 16 && ((y() > mario->y()) &&
		(y() < mario->y() + 32)) && mario->isSpinning())
		dying = true;

	if (one_shooted)
		dying = true;

	if (dying)
	{
		death_counter++;
		if (death_counter == 1)
		{
			new Hit_pixmap(x(), y() - 16);
			Sounds::instance()->play("kick");
		}

		if (death_counter == death_duration)
			die();
	}

	if (disable(range))
		notmove = true;

	else
	{
		notmove = false;

		if (!upsidedown)
		{
			//don't move if mario is on the pipe OR if mario is near the pipe
			if (mario->x() > pos.x() - 32 && mario->x() < pos.x() + 32 && (pause == 0 && advance_counter == 0))
				notmove = true;
			else
				notmove = false;
		}

		if (fire_plant)
		{
			//define the proper index for the texture  
				//based on mario->x() compared to x()
			if (!upsidedown)
			{				
				if (mario->y() <= pos.y() - 5 * 16)
					tex = 3;
				else
					tex = 1;
			}

			else
			{
				if (mario->y() <= pos.y() - 5 * 16)
					tex = 1;
				else
					tex = 3;
			}

			if (!upsidedown)
			{
				if (pause == 10)
				{
					if (!done)
					{
						shoot();				//shoot a fire ball
						done = true;			//don't shoot again
					}
					else
						done = false;
				}
			}

			else
			{
				if (pause == 165)
				{
					if (!done)
					{
						shoot();				//shoot a fire ball
						done = true;			//don't shoot again
					}
					else
						done = false;
				}
			}

			if (mario->x() > pos.x())
				dir = RIGHT;
			else
				dir = LEFT;

			if (!upsidedown)
			{
				if (!notmove && pause >= 0)
				{
					if (advance_counter <= 32 && pause == 0)
					{
						//go up
						setY(y() - 1);
						advance_counter++;
					}
					if (pause <= 175 && advance_counter >= 32)
					{
						pause++;
						mouth = true;
					}
					if (pause == 175 && advance_counter >= 0)
					{
						//go down
						setY(y() + 1);
						advance_counter--;
						mouth = false;
					}
					if (advance_counter == 0)
						pause--;
				}
			}

			else
			{
				if (!notmove && pause >= 0) {
					if (advance_counter <= 32 && pause == 0)
					{
						//go down
						setY(y() - 1);
						advance_counter++;
						mouth = false;
					}

					if (pause <= 175 && advance_counter >= 32)
						pause++;

					if (pause == 175 && advance_counter >= 0)
					{
						//go up
						setY(y() + 1);
						advance_counter--;
					}

					if (advance_counter == 0)
					{
						pause--;
						mouth = true;
					}
				}
			}
		}

		else
		{
			if (!notmove && pause >= 0)
			{
				if (advance_counter <= 32 && pause == 0)
				{
					//go up
					setY(y() - 1);
					advance_counter++;
				}

				if (pause <= 100 && advance_counter >= 32)
					pause++;

				if (pause == 100 && advance_counter >= 0)
				{
					//go down
					setY(y() + 1);
					advance_counter--;
				}

				if (advance_counter == 0)
					pause--;
			}
		}
	}
}

void Plant::animate()
{
	Entity::animate();

	if (dying)
		setPixmap(texture_cloud[(death_counter / 5) % 4]);
	else
	{
		if (fire_plant)
		{
			if (upsidedown)
			{
				if (mouth)
					setPixmap(texture_fireplant[tex - 1].transformed(QTransform().scale(1, -1)));

				else if (tex == 3)
					setPixmap(texture_fireplant[tex].transformed(QTransform().scale(1, -1)));

				else if (tex == 1)
					setPixmap(texture_fireplant[tex].transformed(QTransform().scale(1, -1)));
			}
			else
			{
				if (mouth)
					setPixmap(texture_fireplant[tex - 1]);

				else if (tex == 3)
					setPixmap(texture_fireplant[tex]);

				else if (tex == 1)
					setPixmap(texture_fireplant[tex]);
			}
		}
		else
			setPixmap(texture_biteplant[(pause / 10) % 2]);

		if (dir == RIGHT)
			setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));
	}
}

void Plant::shoot()
{
	//spawn a different typer of Fire_ball object based on 
	//the class variables upsidedown, dir and tex
	if (!upsidedown)
	{
		if (dir == LEFT && tex == 3)
			new fire_ball(pos, mario, LEFT, UP, false);
		else if (dir == RIGHT && tex == 3)
			new fire_ball(pos, mario, RIGHT, UP, false);
		else if (dir == LEFT)
			new fire_ball(pos, mario, LEFT, DOWN, false);
		else if (dir == RIGHT)
			new fire_ball(pos, mario, RIGHT, DOWN, false);
	}

	else
	{
		if (dir == LEFT && tex == 3)
			new fire_ball(pos, mario, LEFT, DOWN, true);
		else if (dir == RIGHT && tex == 3)
			new fire_ball(pos, mario, RIGHT, DOWN, true);
		else if (dir == LEFT)
			new fire_ball(pos, mario, LEFT, UP, true);
		else if (dir == RIGHT)
			new fire_ball(pos, mario, RIGHT, UP, true);
	}
}

void Plant::hurt()
{
	collidable = false;
	dying = true;
}