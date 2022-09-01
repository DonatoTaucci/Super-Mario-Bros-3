#include "Koopa.h"
#include "Wing.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"
#include "Point.h"
#include "Hit_pixmap.h"



Koopa::Koopa(QPoint position, bool _winged, Direction direction) : Enemy()
{
	// textures
	texture_walk[0] = Sprites::instance()->get("koopa-walk-0");
	texture_walk[1] = Sprites::instance()->get("koopa-walk-1");
	texture_smashed = Sprites::instance()->get("koopa-smashed");
	texture_roll[0] = Sprites::instance()->get("koopa-roll-0");
	texture_roll[1] = Sprites::instance()->get("koopa-roll-1");
	texture_roll[2] = Sprites::instance()->get("koopa-roll-2");
	texture_awaking[0] = Sprites::instance()->get("koopa-awaking-0");
	texture_awaking[1] = Sprites::instance()->get("koopa-awaking-1");

	//set flags
	hitted = false;
	roll = false;
	reverse_texture = false;
	picked_up = false;
	thrown_away = false;
	check = false;
	winged = _winged;
	
	//set direction
	dir = direction;

	//set counter
	smashed_counter = 0;
	counter = -1;
	invu_counter = -10;
	death_duration = 400;

	//set other class variables
	range = 240;
	animation_div = 8;
	falling_speed = 2;
	
	if (winged)
	{
		jumping_duration = 3.5 * 16;
		jumping_speed = 2;
		falling_speed = 3;
		new Wing(position, 0, this, false, false);
	}

	// set starting pixmap, positions and Z value
	setPixmap(texture_walk[0]);
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(1);
}

void Koopa::advance()
{
	if(mario == 0)
		mario = Game::instance()->getMario();

	if (!disable(range))
	{
		if ((x() < mario->x() + 2 * 16) && x() > mario->x() - 2 * 16 && ((y() > mario->y()) &&
			(y() < mario->y() + 32)) && mario->isSpinning())
		{
			if (hitted)
			{
				if (roll)
					roll = false;

				smashed_counter = 0;
			}
			one_shooted = true;
		}

		if (one_shooted)
		{
			death_counter++;

			if (winged)
				hurt();

			if (!hitted)
				hurt();

			if (dir == RIGHT)
				setX(x() + 1);
			
			else if (dir == LEFT)
				setX(x() - 1);

			if (death_counter == 1)
			{
				new Hit_pixmap(x(), y() - 16);
				new Point(x(), y(), 200);

				hitted = true;
				collidable = false;
				reverse_texture = true;
				falling = false;
				jumping_duration = 3.5 * 16;
				startJumping();
			}	
		}

		if (picked_up)
		{
			if (moving)
				moving = false;

			if (!check)
				check = true;


			if (collidable)
				collidable = false;

			if (!mario->isBig())
				setY(mario->y() - 2);

			else
				setY(mario->y() + 6);

			if (mario->getDir() == RIGHT)
				setX(mario->x() + 8);

			else if (mario->getDir() == LEFT)
				setX(mario->x() - 8);

			if (!mario->getPickKoopa())
				picked_up = false;
		}

		if (check && !picked_up)
		{
			thrown_away = true;
			moving_speed = 2;
			collidable = true;
			setDirection(mario->getDir());
			mario->setKickCounter(0);

			if (dir == LEFT)
				setX(x() - 12);
			else if (dir == RIGHT)
				setX(x() + 12);

			roll = true;
			moving = true;
			check = false;
		}

		if (thrown_away)
		{
			counter++;
			
			if (counter == 1)
			{
				thrown_away = false;
				counter = -1;
			}
		}
		
		else
		{
			if (!hitted && !roll)
				moving_speed = animation_counter % 2;

			if (winged)
				startJumping();

			// moving
			if (moving)
			{
				if (freezed)
					return;

				prevPos = pos();

				if (dir == RIGHT)
					setX(x() + moving_speed);
				else if (dir == LEFT)
					setX(x() - moving_speed);
				else if (dir == UP)
					setY(y() - moving_speed);
				else if (dir == DOWN)
					setY(y() + moving_speed);

				solveCollisions();
			}

			// jumping
			if (jumping)
			{
				if (freezed)
					return;
				prevPos = pos();

				// move upwards
				if (jump_counter > jumping_duration - 30)
					setY(y() - 1);
				
				else
					setY(y() - jumping_speed);

				// increase jump frame count
				jump_counter += jumping_speed;

				// end jumping when frame count reaches the defined limit
				if (jump_counter > jumping_duration)
					endJumping();

				solveCollisions();
			}

			// if the entity is not touching its walkable object anymore
			// we have to start falling
			if (walkable_object && !touchingDirection(walkable_object))
			{
				walkable_object = 0;
				falling = true;
			}

			// falling
			if (falling)
			{
				if (freezed)
					return;
				prevPos = QPointF((int)x(), (int)y());

				if (falling_counter <= 10)
					setY(y() + 1);
				
				else if (falling_counter <= 15)
					setY(y() + 2);
				
				else
					setY(y() + falling_speed);

				falling_counter++;

				solveCollisions();
			}

			// if we fall beyond the scene bottom limit
			// we have to die (if not dead already)
			if (y() > Game::instance()->getScene()->sceneRect().height() && !dead)
				one_shooted = true;
		}
	}
}

void Koopa::animate()
{
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if(hitted && !roll && reverse_texture)
		setPixmap(texture_smashed.transformed(QTransform().scale(1, -1)));
	else if (hitted && !roll)
	{
		setPixmap(texture_smashed);

		if (!picked_up)
			smashed_counter++;

		if (smashed_counter >= 350 && smashed_counter < 400)
			setPixmap(texture_awaking[(animation_counter / 5) % 2]);
		
		if (smashed_counter == death_duration)
		{
			moving = true;
			dead = false;
			smashed_counter = 0;
			hitted = false;
		}
	}
	
	if (reverse_texture && !roll)
		setPixmap(texture_roll[0]);
	
	else if (moving && roll && reverse_texture)
	{
		if (invu_counter < 0)
			invu_counter++;
		setPixmap(texture_roll[(animation_counter / 2) % 3].transformed(QTransform().scale(1, -1)));
	}
	
	else if (moving && roll)
	{
		if(invu_counter < 0)
			invu_counter++;
		setPixmap(texture_roll[(animation_counter / 2) % 3]);
	}

	if (moving && !roll && !one_shooted)
		setPixmap(texture_walk[(animation_counter / animation_div) % 2]);

	if (moving && dir == RIGHT)
		setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));

	if (one_shooted)
		setPixmap(texture_smashed.transformed(QTransform().scale(1, -1)));

	// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));
}

void Koopa::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);

	Mario* mario = dynamic_cast<Mario*>(what);

	Koopa* koopa = dynamic_cast<Koopa*>(what);

	if ( (koopa && hitted && roll) || koopa && koopa->getRoll() && koopa->getHitted())
	{
		one_shooted = true;
		collidable = false;

		Sounds::instance()->play("kick");
	}

	if (dynamic_cast<Inert*>(what) && (fromDir == LEFT || fromDir == RIGHT) )
	{
		if (roll)
			Sounds::instance()->play("bump");
		
		if (fromDir == RIGHT)
			setDirection(LEFT);
		
		else
			setDirection(RIGHT);
	}

	Enemy* en = dynamic_cast<Enemy*>(what);

	if (en)
	{
		if (!roll)
		{
			if (fromDir == RIGHT)
				setDirection(LEFT);

			else
				setDirection(RIGHT);
		}
		else
			en->oneShooted();
	}

	if (mario && fromDir == UP && hitted && !roll && !moving)
	{
		if (fromDir == RIGHT)
			setDirection(LEFT);
		else if(fromDir == LEFT)
			setDirection(RIGHT);
		
		moving_speed = 2;
		smashed_counter = 0;
		moving = true;
		roll = true;
		mario->bounce();
	}
	
	else if (mario && roll && fromDir == UP)
	{
		roll = false;
		moving = false;
		mario->bounce();
	}

	else if (mario && roll)
	{
		if(mario->getInvCounter() < 0)
			mario->MarioHurt();		
	}
	
	else if (mario && (fromDir == RIGHT || fromDir == LEFT) && hitted)
	{
		moving_speed = 2;
		
		if (fromDir == RIGHT)
			setDirection(LEFT);
		else if(fromDir == LEFT)
			setDirection(RIGHT);

		moving = true;
		roll = true;
	}
}

void Koopa::hurt()
{
	if (winged)
	{
		winged = false;
		endJumping();
		Sounds::instance()->play("stomp");
		new Point(x(), y(), 100);
		return;
	}
	
	else
	{
		roll = false;
		
		if (death_counter == 0 && !picked_up)
			new Point(x(), y(), 200);
			
		hitted = true;
		moving = false;
		Sounds::instance()->play("stomp");
	}
}

QPainterPath Koopa::shape() const
{
	QPainterPath path;

	if (!hitted)
		path.addRect(0, 8, 16, 17);
	
	else if (hitted)
		path.addRect(0, 0, 17, 16);
	
	return path;
}

void Koopa::solveCollisions()
{
	if (mario->isStatue())
		special_case = true;				//ignore collisions with mario

	Entity::solveCollisions();

	if (special_case)
		special_case = false;
}


