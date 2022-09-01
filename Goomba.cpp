#include "Goomba.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"
#include "Wing.h"
#include "Point.h"
#include "Hit_pixmap.h"


Goomba::Goomba(QPoint position, bool isWinged, Direction direction) : Enemy()
{
	// textures
	texture_walk[0] = Sprites::instance()->get("goomba-walk-0");
	texture_walk[1] = Sprites::instance()->get("goomba-walk-1");
	texture_smashed = Sprites::instance()->get("goomba-brown-smashed");

	//set direction
	dir = direction;

	//set flags
	slow_wing = false;
	fast_wing = false;
	death_flag = false;
	reverse_texture = false;
	winged = isWinged;

	//set counter
	flyng_counter = -1;
	death_duration = 100;


	if (winged)
	{
		//ignore all the collisions with other enemies
		special_case_2 = true;
		new Wing(position, this, 0, true, false);
	}

	//set other class variables
	range = 240;		
	moving_div = 8;

	//set starting pixmap, position and Z value
	setPixmap(texture_walk[0]);
	setPos(position-QPoint(0, pixmap().height()));
	setZValue(3);
}

void Goomba::advance()
{
	if (mario == 0)
		mario = Game::instance()->getMario();

	if (!disable(range))
	{
		if ((x() < mario->x() + 2 * 16) && x() > mario->x() && ((y() > mario->y()) &&
			(y() < mario->y() + 32)) && mario->isSpinning() && one_shooted == false)
			one_shooted = true;

		if ((x() < mario->x()) && x() > mario->x() - 2 * 16 && ((y() > mario->y()) &&
			(y() < mario->y() + 32)) && mario->isSpinning() && one_shooted == false)
			one_shooted = true;

		if (one_shooted)
		{
			if (death_counter == 1)
			{
				new Hit_pixmap(x(), y() - 16);
				new Point(x(), y(), 200);

				reverse_texture = true;
				collidable = false;
				falling = false;

				jumping_speed = 2;
				falling_speed = 2;
				jumping_duration = 2.5 * 16;

				startJumping();

				Sounds::instance()->play("kick");
			}

			dying = true;

			if (winged)
				winged = false;
		}

		// half speed
		moving_speed = animation_counter % 2;

		if (winged)
		{
			flyng_counter++;

			if (flyng_counter >= 60 && flyng_counter <= 95)
			{
				jumping_speed = 1;
				falling_speed = 1;
				jumping_duration = 0.5 * 16;
				startJumping();
				slow_wing = true;
			}
			
			else
				slow_wing = false;
			
			if (flyng_counter >= 120)
			{
				jumping_speed = 2;
				falling_speed = 2;
				jumping_duration = 3 * 16;
				startJumping();
				flyng_counter = -1;
				fast_wing = true;
			}
		}

		if (moving)
		{
			if (freezed)
				return;

			if (slow_wing)
				moving_speed = animation_counter % moving_speed_div == 0;

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
		if (falling && winged)
		{
			if (freezed)
				return;
			prevPos = QPointF((int)x(), (int)y());

			if (falling_counter <= 10)
				setY(y() + 1);
			
			else
				setY(y() + falling_speed);

			falling_counter++;

			falling_counter += falling_speed;

			solveCollisions();
			fast_wing = false;
		}

		else if (falling)
		{
			if (freezed)
				return;
			prevPos = QPointF((int)x(), (int)y());

			setY(y() + falling_speed);

			falling_counter++;

			solveCollisions();
			fast_wing = false;
		}

		// if we fall beyond the scene bottom limit
		// we have to die (if not dead already)
		if (y() > Game::instance()->getScene()->sceneRect().height() && !dead)
			one_shooted = true;

	}
}

void Goomba::animate()
{
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	// set the proper texture
	if (reverse_texture)
		setPixmap(texture_walk[0].transformed(QTransform().scale(1, -1)));

	else if (dying)
		setPixmap(texture_smashed);

	else if (moving)
		setPixmap(texture_walk[(animation_counter / moving_div) % 2]);

	// correct y position if texture height changed
	int cur_h = boundingRect().height();
	if (prev_h != cur_h)
		setY(y() - (cur_h - prev_h));
}


void Goomba::hit(Object *what, Direction fromDir)
{
	if( (dynamic_cast<Inert*>(what) || dynamic_cast<Enemy*>(what))
		&& (fromDir == LEFT || fromDir == RIGHT))
		dir = inverse(dir);

	Object::hit(what, fromDir);
}

void Goomba::hurt()
{
	if (winged)
	{
		winged = false;
		special_case_2 = false;
		setPixmap(texture_walk[0]);
		new Point(x(), y(), 100);
		Sounds::instance()->play("stomp");
	}
	
	else
	{
		dying = true;
		moving = false;
		
		new Point(x(), y(), 200);
		
		Sounds::instance()->play("stomp");
	}	
}

void Goomba::solveCollisions()
{
	if (mario->isStatue())
		special_case = true;			//ignore collisions with mario

	Entity::solveCollisions();

	if (special_case)
		special_case = false;
}

