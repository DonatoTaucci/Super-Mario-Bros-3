#include "Secret_box.h"
#include "Coin.h"

SecretBox::SecretBox(QPoint position, spawnable_type spawnable, bool _big) : Inert()
{
	//pointer
	mario = 0;

	// set flags
	active = true;
	content = spawnable;
	big = _big;

	//set counters
	hit_counter = -1;
	animation_counter = 0;

	// textures
	if (!big)
	{
		texture_active[0] = Sprites::instance()->get("secret-box-0");
		texture_active[1] = Sprites::instance()->get("secret-box-1");
		texture_active[2] = Sprites::instance()->get("secret-box-2");
		texture_active[3] = Sprites::instance()->get("secret-box-3");
		texture_inactive = Sprites::instance()->get("secret-box-inactive");

		setPixmap(texture_active[0]);
	}

	else
	{
		texture_big_active = Sprites::instance()->get("secret-box-big-active");
		texture_big_inactive = Sprites::instance()->get("secret-box-big-inactive");

		setPixmap(texture_big_active);
	}

	//set starting position and Z value
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(3);
}

void SecretBox::animate()
{
	if (!big)
	{
		if (active)
		{
			animation_counter++;
			setPixmap(texture_active[(animation_counter / 10) % 4]);
		}

		else
			setPixmap(texture_inactive);
	}
	else if (!active)
		setPixmap(texture_big_inactive);
}

void SecretBox::advance()
{
	if (!big)
	{
		if (hit_counter >= 0)
		{
			if (hit_counter < 12)
			{
				setY(y() - 1);
				hit_counter++;
			}

			if (hit_counter >= 12 && hit_counter < 24)
			{
				setY(y() + 1);
				hit_counter++;
			}
		}
		else
			hit_counter = -1;
	}
}

void SecretBox::hit(Object* what, Direction fromDir)
{
	mario = dynamic_cast<Mario*>(what);

	if (mario && fromDir == DOWN)
	{
		if (active && !big)
		{
			hit_counter = 0;
			active = false;
			Sounds::instance()->play("bump");

			if (content == COIN)
			{
				new Coin(QPoint(x(), y()));					// spawn coin object
				Sounds::instance()->play("coin");
			}

			else if (content == LEAF)
			{
				if (mario->isBig())
					new Leaf(QPoint(x(), y()));				// spawn leaf object

				else
				{
					Sounds::instance()->play("spawn");
					new Mushroom(QPoint(x(), y()));			// spawn mushroom object
				}

			}
			if (content == FLOWER)
			{
				if (mario->isBig());						// spawn flower object

				else
				{
					Sounds::instance()->play("spawn");
					new Mushroom(QPoint(x(), y()));			// spawn mushroom object
				}
			}				
		}
		else if (active && big)
		{
			active = false;
			if (content == TANOOKI)
				new Tanooki(QPoint(x() + 0.5 * 16, y()));
		}
		else return;
	}
}
