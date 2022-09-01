#include "Mario.h"
#include "Game.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Enemy.h"
#include "Koopa.h"
#include "Fire_ball.h"
#include "Plant.h"

Mario::Mario(QPoint position, bool _big, bool _raccoon, bool _tanooki) : Entity()
{
	// textures
	texture_stand[0]		  = Sprites::instance()->get("mario-small-stand");
	texture_stand[1]		  = Sprites::instance()->get("mario-big-stand");
	texture_stand[2]		  = Sprites::instance()->get("mario-raccoon-stand");
	texture_stand[3]		  = Sprites::instance()->get("mario-tanooki-stand");
	texture_jumping[0]		  = Sprites::instance()->get("mario-small-jump");
	texture_jumping[1]		  = Sprites::instance()->get("mario-big-jump");
	texture_jumping[2]		  = Sprites::instance()->get("mario-raccoon-jump");
	texture_jumping[3]		  = Sprites::instance()->get("mario-tanooki-jump");
	texture_jump_run[0]		  = Sprites::instance()->get("mario-small-jump-run");
	texture_jump_run[1]		  = Sprites::instance()->get("mario-big-jump-run");
	texture_jump_run[2]		  = Sprites::instance()->get("mario-raccoon-jump-run");
	texture_jump_run[3]		  = Sprites::instance()->get("mario-tanooki-jump-run");
	texture_fall_run[0]		  = Sprites::instance()->get("mario-small-fall-run");
	texture_fall_run[1]		  = Sprites::instance()->get("mario-big-fall-run");
	texture_fall_run[2]		  = Sprites::instance()->get("mario-raccoon-fall-run");
	texture_fall_run[3]		  = Sprites::instance()->get("mario-tanooki-fall-run");
	texture_falling[0]		  = Sprites::instance()->get("mario-small-fall");
	texture_falling[1]		  = Sprites::instance()->get("mario-big-fall");
	texture_falling[2]		  = Sprites::instance()->get("mario-raccoon-fall");
	texture_falling[3]		  = Sprites::instance()->get("mario-tanooki-fall");
	texture_brake[0]		  = Sprites::instance()->get("mario-small-brake");
	texture_brake[1]		  = Sprites::instance()->get("mario-big-brake");
	texture_brake[2]		  = Sprites::instance()->get("mario-raccoon-brake");
	texture_brake[3]		  = Sprites::instance()->get("mario-tanooki-brake");
	texture_kick[0]			  = Sprites::instance()->get("mario-small-kick");
	texture_kick[1]			  = Sprites::instance()->get("mario-big-kick");
	texture_kick[2]			  = Sprites::instance()->get("mario-raccoon-kick");
	texture_kick[3]			  = Sprites::instance()->get("mario-tanooki-kick");
	texture_crouch[0]		  = Sprites::instance()->get("mario-big-crouch");
	texture_crouch[1]		  = Sprites::instance()->get("mario-raccoon-crouch");
	texture_crouch[2]		  = Sprites::instance()->get("mario-tanooki-crouch");
	texture_walking[0][0]	  = Sprites::instance()->get("mario-small-walk-0");
	texture_walking[0][1]	  = Sprites::instance()->get("mario-small-walk-1");
	texture_walking[0][2]	  = Sprites::instance()->get("mario-small-walk-2");
	texture_walking[0][3]	  = Sprites::instance()->get("mario-small-walk-3");
	texture_walking[1][0]	  = Sprites::instance()->get("mario-big-walk-0");
	texture_walking[1][1]	  = Sprites::instance()->get("mario-big-walk-1");
	texture_walking[1][2]	  = Sprites::instance()->get("mario-big-walk-2");
	texture_walking[1][3]	  = Sprites::instance()->get("mario-big-walk-3");
	texture_run[0][0]		  = Sprites::instance()->get("mario-small-run-0");
	texture_run[0][1]		  = Sprites::instance()->get("mario-small-run-1");
	texture_run[0][2]		  = Sprites::instance()->get("mario-small-run-2");
	texture_run[0][3]		  = Sprites::instance()->get("mario-small-run-3");
	texture_run[1][0]		  = Sprites::instance()->get("mario-big-run-0");
	texture_run[1][1]		  = Sprites::instance()->get("mario-big-run-1");
	texture_run[1][2]		  = Sprites::instance()->get("mario-big-run-2");
	texture_run[1][3]		  = Sprites::instance()->get("mario-big-run-3");
	texture_run[2][0]		  = Sprites::instance()->get("mario-raccoon-run-0");
	texture_run[2][1]		  = Sprites::instance()->get("mario-raccoon-run-1");
	texture_run[2][2]		  = Sprites::instance()->get("mario-raccoon-run-2");
	texture_run[2][3]		  = texture_run[2][0];
	texture_run[3][0]		  = Sprites::instance()->get("mario-tanooki-run-0");
	texture_run[3][1]		  = Sprites::instance()->get("mario-tanooki-run-1");
	texture_run[3][2]		  = Sprites::instance()->get("mario-tanooki-run-2");
	texture_run[3][3]		  = texture_run[3][0];
	texture_pipe[0]			  = Sprites::instance()->get("mario-pipe-small");
	texture_pipe[1]			  = Sprites::instance()->get("mario-pipe-big");
	texture_pipe[2]			  = Sprites::instance()->get("mario-pipe-raccoon");
	texture_pipe[3]			  = Sprites::instance()->get("mario-pipe-tanooki");
	texture_small2big[0]	  = texture_stand[0];
	texture_small2big[1]	  = Sprites::instance()->get("mario-half-transf");
	texture_small2big[2]	  = texture_stand[0];
	texture_small2big[3]	  = Sprites::instance()->get("mario-half-transf");
	texture_small2big[4]	  = texture_stand[0];
	texture_small2big[5]	  = Sprites::instance()->get("mario-half-transf");
	texture_small2big[6]	  = texture_stand[1];
	texture_small2big[7]	  = Sprites::instance()->get("mario-half-transf");
	texture_small2big[8]	  = texture_stand[1];
	texture_small2big[9]	  = Sprites::instance()->get("mario-half-transf");
	texture_small2big[10]	  = texture_stand[1];
	texture_small2big[11]	  = Sprites::instance()->get("mario-half-transf");
	texture_big2small[0]	  = texture_stand[1];
	texture_big2small[1]	  = Sprites::instance()->get("mario-half-transf");
	texture_big2small[2]	  = texture_stand[1];
	texture_big2small[3]	  = Sprites::instance()->get("mario-half-transf");
	texture_big2small[4]	  = texture_stand[1];
	texture_big2small[5]	  = Sprites::instance()->get("mario-half-transf");
	texture_big2small[6]	  = texture_stand[0];
	texture_big2small[7]	  = Sprites::instance()->get("mario-half-transf");
	texture_big2small[8]	  = texture_stand[0];
	texture_big2small[9]	  = Sprites::instance()->get("mario-half-transf");
	texture_big2small[10]	  = texture_stand[0];
	texture_big2small[11]	  = Sprites::instance()->get("mario-half-transf");
	texture_big2raccoon[0]	  = Sprites::instance()->get("transf-cloud-0");
	texture_big2raccoon[1]	  = Sprites::instance()->get("transf-cloud-1");
	texture_big2raccoon[2]	  = Sprites::instance()->get("transf-cloud-2");
	texture_big2raccoon[3]	  = Sprites::instance()->get("transf-cloud-3");
	texture_big2raccoon[4]	  = texture_stand[2];
	texture_raccoon2big[0]	  = Sprites::instance()->get("transf-cloud-0");
	texture_raccoon2big[1]	  = Sprites::instance()->get("transf-cloud-1");
	texture_raccoon2big[2]	  = Sprites::instance()->get("transf-cloud-2");
	texture_raccoon2big[3]	  = Sprites::instance()->get("transf-cloud-3");
	texture_raccoon2big[4]	  = texture_stand[1];
	texture_cloud[0]		  = Sprites::instance()->get("transf-cloud-0");
	texture_cloud[1]		  = Sprites::instance()->get("transf-cloud-1");
	texture_cloud[2]		  = Sprites::instance()->get("transf-cloud-2");
	texture_cloud[3]		  = Sprites::instance()->get("transf-cloud-3");
	texture_big2tanooki[0]	  = Sprites::instance()->get("transf-cloud-0");
	texture_big2tanooki[1]	  = Sprites::instance()->get("transf-cloud-1");
	texture_big2tanooki[2]	  = Sprites::instance()->get("transf-cloud-2");
	texture_big2tanooki[3]	  = Sprites::instance()->get("transf-cloud-3");
	texture_big2tanooki[4]	  = texture_stand[3];
	texture_tanooki2big[0]	  = Sprites::instance()->get("transf-cloud-0");
	texture_tanooki2big[1]	  = Sprites::instance()->get("transf-cloud-1");
	texture_tanooki2big[2]	  = Sprites::instance()->get("transf-cloud-2");
	texture_tanooki2big[3]	  = Sprites::instance()->get("transf-cloud-3");
	texture_tanooki2big[4]	  = texture_stand[1];
	texture_inv_walk[0][0]	  = Sprites::instance()->get("mario-small-walk-0");
	texture_inv_walk[0][1]	  = Sprites::instance()->get("mario-small-inv");
	texture_inv_walk[0][2]	  = Sprites::instance()->get("mario-small-walk-1");
	texture_inv_walk[0][3]	  = Sprites::instance()->get("mario-small-inv");
	texture_inv_walk[0][4]	  = Sprites::instance()->get("mario-small-walk-2");
	texture_inv_walk[0][5]	  = Sprites::instance()->get("mario-small-inv");
	texture_inv_walk[0][6]	  = Sprites::instance()->get("mario-small-walk-3");
	texture_inv_walk[1][0]	  = Sprites::instance()->get("mario-big-walk-0");
	texture_inv_walk[1][1]	  = Sprites::instance()->get("mario-small-inv");
	texture_inv_walk[1][2]	  = Sprites::instance()->get("mario-big-walk-1");
	texture_inv_walk[1][3]	  = Sprites::instance()->get("mario-small-inv");
	texture_inv_walk[1][4]	  = Sprites::instance()->get("mario-big-walk-2");
	texture_inv_walk[1][5]	  = Sprites::instance()->get("mario-small-inv");
	texture_inv_walk[1][6]	  = Sprites::instance()->get("mario-big-walk-3");
	texture_inv_stand[0][0]	  = Sprites::instance()->get("mario-small-stand");
	texture_inv_stand[0][1]	  = Sprites::instance()->get("mario-small-inv");
	texture_inv_stand[1][0]	  = Sprites::instance()->get("mario-big-stand");
	texture_inv_stand[1][1]	  = Sprites::instance()->get("mario-small-inv");
	texture_inv_jumping[0][0] = Sprites::instance()->get("mario-small-jump");
	texture_inv_jumping[0][1] = Sprites::instance()->get("mario-small-inv");
	texture_inv_jumping[1][0] = Sprites::instance()->get("mario-big-jump");
	texture_inv_jumping[1][1] = Sprites::instance()->get("mario-small-inv");
	texture_inv_falling[0][0] = Sprites::instance()->get("mario-small-fall");
	texture_inv_falling[0][1] = Sprites::instance()->get("mario-small-inv");
	texture_inv_falling[1][0] = Sprites::instance()->get("mario-big-fall");
	texture_inv_falling[1][1] = Sprites::instance()->get("mario-small-inv");
	texture_walking[2][0]	  = Sprites::instance()->get("mario-raccoon-walk-0");
	texture_walking[2][1]	  = Sprites::instance()->get("mario-raccoon-walk-1");
	texture_walking[2][2]	  = Sprites::instance()->get("mario-raccoon-walk-2");
	texture_walking[2][3]	  = Sprites::instance()->get("mario-raccoon-walk-3");
	texture_walking[3][0]	  = Sprites::instance()->get("mario-tanooki-walk-0");
	texture_walking[3][1]	  = Sprites::instance()->get("mario-tanooki-walk-1");
	texture_walking[3][2]	  = Sprites::instance()->get("mario-tanooki-walk-2");
	texture_walking[3][3]	  = Sprites::instance()->get("mario-tanooki-walk-3");
	texture_death			  = Sprites::instance()->get("mario-death");
	texture_spin[0][0]		  = Sprites::instance()->get("mario-raccoon-spin-0");
	texture_spin[0][1]		  = Sprites::instance()->get("mario-raccoon-spin-1");
	texture_spin[0][2]		  = Sprites::instance()->get("mario-raccoon-spin-2");
	texture_spin[0][3]		  = texture_spin[0][1];
	texture_spin[1][0]		  = Sprites::instance()->get("mario-tanooki-spin-0");
	texture_spin[1][1]		  = Sprites::instance()->get("mario-tanooki-spin-1");
	texture_spin[1][2]		  = Sprites::instance()->get("mario-tanooki-spin-2");
	texture_spin[1][3]		  = texture_spin[1][1];
	texture_gliding[0][0]	  = Sprites::instance()->get("mario-raccoon-gliding-0");
	texture_gliding[0][1]	  = Sprites::instance()->get("mario-raccoon-gliding-1");
	texture_gliding[1][0]	  = Sprites::instance()->get("mario-tanooki-gliding-0");
	texture_gliding[1][1]	  = Sprites::instance()->get("mario-tanooki-gliding-1");
	texture_flying[0][0]	  = Sprites::instance()->get("mario-raccoon-jump-run");
	texture_flying[0][1]	  = Sprites::instance()->get("mario-raccoon-flying");
	texture_flying[0][2]	  = Sprites::instance()->get("mario-raccoon-fall-run");
	texture_flying[1][0]	  = Sprites::instance()->get("mario-tanooki-jump-run");
	texture_flying[1][1]	  = Sprites::instance()->get("mario-tanooki-flying");
	texture_flying[1][2]	  = Sprites::instance()->get("mario-tanooki-fall-run");
	texture_statue[0]		  = Sprites::instance()->get("mario-tanooki-statue");
	texture_statue[1]		  = Sprites::instance()->get("mario-tanooki-statue-void");
	texture_pick_koopa[0][0]  = Sprites::instance()->get("mario-small-pick-koopa-0");
	texture_pick_koopa[0][1]  = Sprites::instance()->get("mario-small-pick-koopa-1");
	texture_pick_koopa[0][2]  = texture_pick_koopa[0][0];
	texture_pick_koopa[0][3]  = texture_pick_koopa[0][1];
	texture_pick_koopa[1][0]  = Sprites::instance()->get("mario-big-pick-koopa-0");
	texture_pick_koopa[1][1]  = Sprites::instance()->get("mario-big-pick-koopa-1");
	texture_pick_koopa[1][2]  = Sprites::instance()->get("mario-big-pick-koopa-2");
	texture_pick_koopa[1][3]  = texture_pick_koopa[1][1];
	texture_pick_koopa[2][0]  = Sprites::instance()->get("mario-raccoon-pick-koopa-0");
	texture_pick_koopa[2][1]  = Sprites::instance()->get("mario-raccoon-pick-koopa-1");
	texture_pick_koopa[2][2]  = Sprites::instance()->get("mario-raccoon-pick-koopa-2");
	texture_pick_koopa[2][3]  = texture_pick_koopa[2][1];
	texture_pick_koopa[3][0]  = Sprites::instance()->get("mario-tanooki-pick-koopa-0");
	texture_pick_koopa[3][1]  = Sprites::instance()->get("mario-tanooki-pick-koopa-1");
	texture_pick_koopa[3][2]  = Sprites::instance()->get("mario-tanooki-pick-koopa-2");
	texture_pick_koopa[3][3]  = texture_pick_koopa[3][1];

	// set flags
	big = _big;
	raccoon = _raccoon;
	tanooki = _tanooki;
	crouch = false;
	moving = false;
	running = false;
	spinning = false;
	gliding = false;
	flying = false;
	change_scene = false;
	statue = false;
	pick_koopa = false;
	pipe_check = false;
	become_big = false;

	// set counters
	moving_start_counter = -1;
	moving_stop_counter = -1;
	dir_change_counter = -1;
	transformation_counter = -1;
	inv_counter = -1;
	kick_counter = -1;
	spinning_counter = -1;
	flying_counter = -1;
	running_counter = -1;
	statue_counter = -1;
	pipe_counter = -1;

	//set other class variables
	prev_dir = dir;
	moving_div = 1;
	jumping_duration = 3.5 * 16;
	death_duration = 150;
	life = 4;

	// set starting pixmap, position and Z value
	setPixmap(texture_stand[big]);
	setPos(position-QPoint(0, pixmap().height()));
	setZValue(3);
}

void Mario::advance()
{
	if (dying)
	{
		if (death_counter == 20)
			startJumping();
		else if (death_counter > 20)
			Entity::advance();

	}
	else
	{
		//when the game ends, starts the finish procedure
		if (Game::instance()->getFinish() && x() < 160 * 16)
		{
			if (dir == LEFT)
				setDirection(RIGHT);

			if (!moving)
				moving = true;

			if (animation_counter % 2 == 0)
				setX(x() + 1);
		}

		//if the player relese the Z key while holding 
		//a koopa, the koopa will be thrown away
		if (pick_koopa && !running)
			pick_koopa = false;

		if (running && moving)
			running_counter++;
		else
		{
			if (running_counter <= 0)
				running_counter = -1;
			else
				running_counter = running_counter - 3;
		}

		//flying
		if (flying)
		{
			flying_counter++;
			falling = false;
			setY(y() - 1);

			if (flying_counter == 20)
			{
				flying = false;
				flying_counter = -1;
				falling = true;
				gliding = true;
			}
		}

		//statue
		if (statue)
		{
			moving = false;
			falling_speed = 4;
			statue_counter++;

			if (statue_counter == 300)
			{
				statue = false;
				statue_counter = 4;
			}
		}

		//spinning
		if (spinning)
		{
			spinning_counter++;
		}

		// update moving acceleration / deceleration counters
		if (moving_stop_counter >= 0)
			moving_stop_counter++;
		else
			moving_start_counter++;

		// update direction change counter
		if (dir_change_counter >= 0)
			dir_change_counter++;
		if (dir_change_counter > 20)
			dir_change_counter = -1;

		//3 different "brake" speeds based on the current speed
		if (dir_change_counter >= 0 && running_counter >= 200 && !dying)
		{
			moving_speed = running_counter % 2 + 1;
			moving_div = 3;
		}
		else if (dir_change_counter >= 0 && running_counter >= 100 && running_counter < 200 && !dying)
		{
			moving_speed = running_counter % 2;
			moving_div = 3;
		}
		else if (dir_change_counter >= 0 && running_counter >= 50 && running_counter < 100 && !dying)
		{
			moving_speed = running_counter % 2;
			moving_div = 5;
		}

		// horizontal acceleration when moving starts and moving stop is not active yet
		//7 different speeds based on running_counter
		else if (moving_start_counter >= 0 && moving_stop_counter < 0)
		{
			if (moving_start_counter < 10)
			{
				moving_speed = moving_start_counter % 2;		
				moving_div = 7;
			}
			if (moving_start_counter >= 10 && moving_start_counter <= 25)
			{
				moving_speed = 1;
				moving_div = 5;
			}
			if (moving_start_counter > 25)
			{
				moving_speed = moving_start_counter % 2 + 1;	
				moving_div = 3;
			}
			if (moving_start_counter > 25 && running_counter > 50 && running_counter < 100 && running)
			{
				moving_speed = 2;
				moving_div = 3;
			}
			if (moving_start_counter > 25 && running_counter >= 100 && running_counter < 200 && running)
			{
				moving_speed = running_counter % 2 + 2;	
				moving_div = 3;
			}

			if (moving_start_counter > 25 && running_counter >= 200 && running_counter < 250 && running)
			{
				moving_speed = 3;
				moving_div = 3;
			}

			if (moving_start_counter > 25 && running_counter >= 250 && running)
			{
				moving_speed = 4;
				moving_div = 3;
			}

			if (running_counter > 250)
				running_counter = 250;

			if (!moving)
				moving_start_counter = 0;
		}

		// horizontal deceleration when moving ends
		else if (moving_start_counter >= 0 && moving_stop_counter >= 0 && !dying)
		{
			// decelerate for the same extent of the initial acceleration (max 30 frames)
			if (moving_stop_counter < std::min(moving_start_counter, 30))
			{
				moving_speed = moving_stop_counter % 2;	// = 0.5 speed
				moving_div = 7;
				moving = true;
			}
			// finally stop
			else
			{
				moving = false;
				moving_start_counter = -1;
				moving_stop_counter = -1;
			}
		}

		//moving
		if (moving)
		{
			if (freezed)
				return;

			if (slow)
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
			//2 different jumping_speed based on
			//jump_counter and jump_duration
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

			//gliding
			if (gliding)
			{
				setY(y() + 1);
				if (flying)
				{
					if (falling_counter == 7)
					{
						gliding = false;
						falling_counter = 0;
					}
				}
				else if (falling_counter == 25)
				{
					gliding = false;
					falling_counter = 0;
				}

			}

			//3 different falling speeds based on the falling_counter
			else if (falling_counter <= 5 && falling_counter >= 1)
				setY(y() + 1);
			else if (falling_counter <= 10)
				setY(y() + 2);
			else
				setY(y() + falling_speed);

			falling_counter++;

			solveCollisions();
		}

		// if mario falls beyond the scene bottom limit
		// has to die (if not dead already)
		if (y() > Game::instance()->getScene()->sceneRect().height() && !dead)
		{
			Game::instance()->losingLife();
			Sounds::instance()->play("death");
			die();
		}
	}

}

// Mario jumps
void Mario::jump()
{
	jumping_duration = 5.5 * 16;

    // start a jump
	jumping_speed = 3;	// reset jumping speed (modified in advance())
    startJumping();

    // if jumping has started, play jump sound
    if(jumping)
        Sounds::instance()->play("jump");
}

// bounce
void Mario::bounce()
{
	// start a small jump
	jumping_duration = 2 * 16;
	falling = false;
	startJumping();
}

// @override setMoving() to add horizontal acceleration
void Mario::setMoving(bool _moving)
{
	// transition move -> stop, then activate moving stop counter
	if(_moving == false && moving && !dying)
		moving_stop_counter = 0;
	// transition stop -> move, then activate moving start counter
	else if(_moving == true && !moving && !dying)
		moving_start_counter = 0;

	Entity::setMoving(_moving);
}

// @override setDirection() to avoid instant direction change
void Mario::setDirection(Direction _dir)
{
	if(_dir != dir && moving)
	{
		// reset acceleration/deceleration counters
		// @TODO: avoid instant direction change
		moving_start_counter = 0;
		moving_stop_counter = -1;

		dir_change_counter = 0;
	}

	// @TODO: avoid instant direction change
	Entity::setDirection(_dir);
}

QPainterPath Mario::shape() const
{
	QPainterPath path;

	if (raccoon && crouch)
		path.addRect(3, 1.2, 10, 18);
	else if (tanooki && crouch)
		path.addRect(3, 1.2, 10, 18);
	//double shape for raccoon and tanooki: with only one it was not possible 
	//to give a correct shape in both directions. With this solution, however, 
	//sometimes Mario can get stuck in a block but in most cases it is possible
	//to free him by changing direction using the directional arrows
	else if (raccoon || tanooki)
	{
		if(dir == LEFT)
			path.addRect(3, 1.2, 10, 28);
		else if(dir == RIGHT)
			path.addRect(8, 1.2, 10, 28);
	}	
	else if (big && crouch)
		path.addRect(3, 1.2, 10, 18);
	else if (big && running)
		path.addRect(3, 1.2, 10, 28);
	else if (big)
		path.addRect(3, 1.2, 10, 28);
	else
		path.addRect(1.2, boundingRect().top(), 10, 16);

	return path;
}

void Mario::animate()
{
	Entity::animate();

	// save current texture height (for later correction)
	int prev_h = boundingRect().height();

	if (dying)
		setPixmap(texture_death);
	else
	{
		if (flying)
		{
			int temp;
			if (raccoon)
				temp = 0;
			else
				temp = 1;

			if (dir == RIGHT)
				setPixmap(texture_flying[temp][(flying_counter / 5) % 3].transformed(QTransform().scale(-1, 1)));
			else
				setPixmap(texture_flying[temp][(flying_counter / 5) % 3]);
		}

		else if (spinning)
		{
			if (raccoon)
			{
				if (dir == RIGHT)
				{
					int temp = (spinning_counter / 5) % 4;
					if (temp != 3)
						setPixmap(texture_spin[0][temp]);
					else
					{
						setPixmap(texture_spin[0][temp].transformed(QTransform().scale(-1, 1)));
						spinning = false;
						spinning_counter = -1;
					}
				}
				else if (dir == LEFT)
				{
					int temp = (spinning_counter / 5) % 4;
					if (temp == 0)
					{
						temp = 2;
						setPixmap(texture_spin[0][temp]);
					}
					else if (temp == 2)
					{
						temp = 0;
						setPixmap(texture_spin[0][temp]);
					}
					else if (temp == 1)
					{
						setPixmap(texture_spin[0][temp].transformed(QTransform().scale(-1, 1)));
					}
					else
					{
						setPixmap(texture_spin[0][temp]);
						spinning = false;
						spinning_counter = -1;
					}
				}
			}

			if (tanooki)
			{
				if (dir == RIGHT)
				{
					int temp = (spinning_counter / 5) % 4;
					if (temp != 3)
						setPixmap(texture_spin[1][temp]);
					else
					{
						setPixmap(texture_spin[1][temp].transformed(QTransform().scale(-1, 1)));
						spinning = false;
						spinning_counter = -1;
					}
				}
				else if (dir == LEFT)
				{
					int temp = (spinning_counter / 5) % 4;
					if (temp == 0)
					{
						temp = 2;
						setPixmap(texture_spin[1][temp]);
					}
					else if (temp == 2)
					{
						temp = 0;
						setPixmap(texture_spin[1][temp]);
					}
					else if (temp == 1)
					{
						setPixmap(texture_spin[1][temp].transformed(QTransform().scale(-1, 1)));
					}
					else
					{
						setPixmap(texture_spin[1][temp]);
						spinning = false;
						spinning_counter = -1;
					}
				}
			}

		}
		else {
			if (raccoon)
				texture_index = 2;
			else if (tanooki)
				texture_index = 3;
			else
				texture_index = big;
			// set the proper texture
			if (kick_counter >= 0)
			{
				if (kick_counter == 1)
					Sounds::instance()->play("kick");
				setPixmap(texture_kick[texture_index]);
				kick_counter++;
				if (kick_counter >= 2 * 5)
					kick_counter = -1;
			}
			else if (transformation_counter >= 0)
			{
				if (raccoon || tanooki || become_big)
				{
					setPixmap(texture_cloud[(transformation_counter / 5) % 4]);
					transformation_counter++;
					if (transformation_counter >= 5 * 4)
					{
						if (become_big)
							become_big = false;

						transformation_counter = -1;
						Game::instance()->setFreezed(false);
					}
				}
				else if (!big)
				{
					if (transformation_counter == 1)
						setY(y() - 14);
					transformation_counter++;
					setPixmap(texture_big2small[(transformation_counter / 5) % 12]);
					if (transformation_counter >= 12 * 5)
					{
						transformation_counter = -1;
						Game::instance()->setFreezed(false);
					}
				}
				else if (!become_big)
				{
					setPixmap(texture_small2big[(transformation_counter / 5) % 12]);
					transformation_counter++;
					if (transformation_counter >= 12 * 5)
					{
						if (pick_koopa)
							setY(y() - 16);
						transformation_counter = -1;
						Game::instance()->setFreezed(false);
					}
				}
				
				
			}
			else if (inv_counter >= 0)
			{
				if (!moving)
					setPixmap(texture_inv_stand[big][(inv_counter / 5) % 2]);

				else if (jumping)
					setPixmap(texture_inv_jumping[big][(inv_counter / 5 % 2)]);

				else if (falling)
					setPixmap(texture_inv_falling[big][(inv_counter / 5) % 2]);
				else
					setPixmap(texture_inv_walk[big][(inv_counter / 5) % 7]);

				inv_counter++;

				if(freezed)
					Game::instance()->setFreezed(false);

				if (inv_counter >= 20 * 5)
					inv_counter = -1;
			}
			else if (big && crouch)
				setPixmap(texture_crouch[0]);
			else if (raccoon && crouch)
				setPixmap(texture_crouch[1]);
			else if (tanooki && crouch)
				setPixmap(texture_crouch[2]);


			else if (jumping)
			{
				if (pick_koopa)
				{
					if (!big)
						setPixmap(texture_pick_koopa[texture_index][1]);
					else
						setPixmap(texture_pick_koopa[texture_index][2]);
				}
				else
					setPixmap(texture_jumping[texture_index]);
			}

			else if (falling)
			{
				if (gliding)
				{
					if (raccoon)
						setPixmap(texture_gliding[0][(falling_counter / 5) % 2]);
					else if (tanooki)
						setPixmap(texture_gliding[1][(falling_counter / 5) % 2]);
				}
				else
				{
					if (pick_koopa)
					{
						if (!big)
							setPixmap(texture_pick_koopa[texture_index][1]);
						else
							setPixmap(texture_pick_koopa[texture_index][2]);
					}
					else
						setPixmap(texture_falling[texture_index]);
				}

			}

			else if (moving)
			{
				if (dir_change_counter > 0 && !pick_koopa)
				{
					if (dir_change_counter == 1)
						Sounds::instance()->play("break");
					setPixmap(texture_brake[texture_index]);

				}
				else
				{
					if (pick_koopa)
						setPixmap(texture_pick_koopa[texture_index][(animation_counter / moving_div) % 4]);
					else
						setPixmap(texture_walking[texture_index][(animation_counter / moving_div) % 4]);
				}
			}
			else
			{
				if (pick_koopa)
					setPixmap(texture_pick_koopa[texture_index][0]);
				else
					setPixmap(texture_stand[texture_index]);
			}



			if (running && running_counter >= 250 && !pick_koopa)
			{

				if (jumping)
					setPixmap(texture_jump_run[texture_index]);

				else
					setPixmap(texture_run[texture_index][(animation_counter / moving_div) % 4]);

				if (falling)
					setPixmap(texture_fall_run[texture_index]);


				if (dir_change_counter > 0)
				{
					if (dir_change_counter == 1)
						Sounds::instance()->play("break");
					setPixmap(texture_brake[texture_index]);

				}
			}


			int cur_h = boundingRect().height();
			if (prev_h != cur_h)
			{
				if ((tanooki && moving_start_counter >= 200 && running) || statue_counter > 0/* || pick_koopa*/)
				{
					setY(y());
				}

				else
				{
					if (!pick_koopa && pipe_counter < 0)
						setY(y() - (cur_h - prev_h));
				}
			}

			// correct y position if texture height changed
			if (transformation_counter > 0)
				moving = false;

			if (statue)
			{
				if (statue_counter >= 0 && statue_counter <= 20)
				{
					if (!freezed)
						Game::instance()->setFreezed(true);

					setPixmap(texture_cloud[(statue_counter / 5) % 4]);
				}

				else
				{
					if (statue_counter >= 20 && statue_counter <= 220)
					{
						if (freezed)
							Game::instance()->setFreezed(false);

						setPixmap(texture_statue[0]);
					}
					else if (statue_counter >= 220 && statue_counter <= 270)
						setPixmap(texture_statue[(statue_counter / 8) % 2]);
					else
						setPixmap(texture_statue[(statue_counter / 4) % 2]);
				}

			}

			if (!statue && statue_counter >= 4)
			{

				if (!freezed)
					Game::instance()->setFreezed(true);

				setPixmap(texture_cloud[(statue_counter / 5) % 4]);

				if (statue_counter >= 20)
				{
					Game::instance()->setFreezed(false);
					statue_counter = -1;
				}

				statue_counter++;
			}

			if (pipe_counter >= 0)
			{
				if (pipe_counter == 1)
				{
					Sounds::instance()->play("pipe");
					Game::instance()->setFreezed(true);
				}
				setPixmap(texture_pipe[texture_index]);

				if (pipe_counter == 1)
					Sounds::instance()->play("pipe");

				if (upDown)
				{
					if (pipe_counter % 2 == 0)
						setY(y() + 1);
				}
				else
				{
					if (pipe_counter % 2 == 0)
						setY(y() - 1);
				}

				pipe_counter++;

				if (pipe_counter == 70 && pipe_check)
				{
					pipe_check = false;
					Game::instance()->setFreezed(false);
					pipe_counter = -1;
				}
					
			}

			// mirror the texture along the horizontal axis if needed
			if (dir == RIGHT)
				setPixmap(pixmap().transformed(QTransform().scale(-1, 1)));

			prev_dir = dir;
		}
	}
}

// Mario has been hit
void Mario::hit(Object *what, Direction fromDir)
{
	Object::hit(what, fromDir);
	
	// disable deceleration if mario hits impenetrable object
	if (dynamic_cast<Inert*>(what) && (fromDir == LEFT || fromDir == RIGHT) && moving_start_counter == -1)
		moving_start_counter = 0;
		

	if (dynamic_cast<Enemy*>(what) && inv_counter >= 0)
		return;

	Koopa* koopa_m = dynamic_cast<Koopa*>(what);

	if (koopa_m && koopa_m->getHitted())
	{
		if (!running)
		{
			kick_counter = 0; // :3
			return;
		}
		else
		{
			pick_koopa = true;
			koopa_m->setPickedUp(true);
			return;
		}
	}

	if (dynamic_cast<Enemy*>(what))
	{
		if (fromDir == DOWN)
		{
			if (dynamic_cast<Plant*>(what))
				MarioHurt();
			else
			{
				dynamic_cast<Enemy*>(what)->hurt();
				bounce();
			}
		}
		else if (fromDir != UNKNOWN)

				MarioHurt();
	

	}

	if (dynamic_cast<Enemy*>(what))
	{
		if (fromDir == LEFT)
		{
			setY(y());
		//	moving = false;
		}
		if (fromDir == RIGHT)
		{
			setY(y());
		//	moving = false;
		}
	}
}

// running = double moving speed
void Mario::setRunning(bool _running)
{
	// do nothing if running state does not change
	if(running == _running)
		return;

	// set new running state
	running = _running;
}

// override die method (Mario is a special case)
void Mario::die()
{
	// call superclass method
	Entity::die();

	// stop level music
	Game::instance()->stopMusic();
}

// crouch
void Mario::setCrouch(bool active)
{
	if(!jumping && !falling)
		crouch = active;
}

void Mario::powerUp()
{
	Sounds::instance()->play("eat");
	transformation_counter = 0;
	big = true;

	Game::instance()->setFreezed(true);
}

void Mario::powerUpLeaf()
{
	
	if (tanooki)
		tanooki = false;
	if (!big)
		powerUp();
	else
	{
		raccoon = true;
		Sounds::instance()->play("raccoon");
	}
		
	transformation_counter = 0;
	

	Game::instance()->setFreezed(true);
}

void Mario::powerUpTanooki()
{
	Sounds::instance()->play("raccoon");
	if(raccoon)
		raccoon = false;

	if (!big)
		big = true;

	tanooki = true;

	transformation_counter = 0;


	Game::instance()->setFreezed(true);
}

void Mario::back2small()
{
	Sounds::instance()->play("pipe");
	transformation_counter = 0;
	big = false;

	inv_counter = 0;

	Game::instance()->setFreezed(true);
}

void Mario::back2big()
{
	Sounds::instance()->play("raccoon");
	inv_counter = 0;
	if (raccoon)
		raccoon = false;
	else if (tanooki)
		tanooki = false;
	big = true;
	transformation_counter = 0;
	Game::instance()->setFreezed(true);
}

void Mario::MarioHurt()
{
	if (statue)
		return;

	if (raccoon || tanooki)
	{
		if (spinning)
		{
			spinning_counter = -1;
			spinning = false;
		}

		become_big = true;

		back2big();
	}
			
	else if (big)
		back2small();
	else
	{
		if (pick_koopa)
			pick_koopa = false;

		falling = false;
		jumping = false;
		jumping_duration = 5 * 16;

		dying = true;
		collidable = false;

		Game::instance()->setFreezed(true);
		Sounds::instance()->play("death");
		Game::instance()->losingLife();

		setZValue(5);

	}
}

void Mario::solveCollisions()
{
	if (inv_counter >= 0)
		special_case = true;
	else
		special_case = false;

	Entity::solveCollisions();
}
