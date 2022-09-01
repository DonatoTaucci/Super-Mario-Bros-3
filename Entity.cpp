#include "Entity.h"
#include "Game.h"
#include "Mario.h"
#include "Fire_ball.h"
#include "Fire_chomper.h"
#include "Koopa.h"
#include "Enemy.h"
#include "Collectable.h"
#include "Leaf.h"
#include "DonutBlock.h"


Entity::Entity() : Object()
{
	//set pointer
	walkable_object = 0;

	//set direction
	dir = RIGHT;

	//set flags
	moving = true;
	jumping = false;
	falling = true;		// we can create entities in mid air and they will fall
	dead = false;
	dying = false;
	freezed = false;
	slow = false;
	special_case = false;
	special_case_2 = false;

	// physics parameters
	moving_speed      = 1;
	jumping_speed     = 3;
	falling_speed	  = 3;
	moving_speed_div  = 2;
	falling_speed_div = 2;

	// counters
	jump_counter      = 0;
	animation_counter = 0;
	death_counter     = 0;

	// durations
	jumping_duration = 30;
	death_duration = 50;
	
}

void Entity::startJumping()
{
    // entity can jump only when it is not falling
	if (!falling && !jumping)
	{
		walkable_object = 0;
		jumping = true;
		jump_counter++;
	}
}

void Entity::endJumping()
{
	if (jumping)
	{
		jumping = false;
		jump_counter = 0;
		falling = true;
	}		

}

void Entity::advance()
{
    // NOTE: every movement is embedded in a prevPos = pos() ... solveCollisions() block
	// this is the only way to check if movement does break the impenetrability hypothesis
	// if it does, we need to revert to previous position

    // moving
    if(moving)
    {
		if (freezed)
			return;

		if (slow)
			moving_speed = animation_counter % moving_speed_div == 0;

        prevPos = pos();

        if(dir == RIGHT)
            setX(x() + moving_speed);
        else if(dir == LEFT)
			setX(x() - moving_speed);
		else if(dir == UP)
			setY(y() - moving_speed);
		else if(dir == DOWN)
			setY(y() + moving_speed);
	
        solveCollisions();
    }

    // jumping
    if(jumping)
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
        if(jump_counter > jumping_duration)
            endJumping();
	
        solveCollisions();
    }

    // if the entity is not touching its walkable object anymore
    // we have to start falling
	if(walkable_object && !touchingDirection(walkable_object))
	{
		walkable_object = 0;
		falling = true;
	}

    // falling
	if(falling)
	{
		if (freezed)
			return;

		if (slow)
			falling_speed = animation_counter % falling_speed_div == 0;

		prevPos = QPointF((int)x(), (int)y());

		//3 different falling speeds based on the falling_counter
		if (falling_counter <= 5 && falling_counter >= 1)
			setY(y() + 1);
		else if (falling_counter <= 10)
			setY(y() + 2);
		else
			setY(y() + falling_speed);

		falling_counter++;

		solveCollisions();
	}

	// if we fall beyond the scene bottom limit
	// we have to die (if not dead already)
	if(y() > Game::instance()->getScene()->sceneRect().height() && !dead)
		die();
}

void Entity::animate()
{
	if (freezed)
		return;
	// increase animation counter
	animation_counter++;

	// increase death counter if dying
	if(dying && !dead)
	{
		death_counter++;
		if(death_counter >= death_duration)
			die();
	}
}

void Entity::solveCollisions()
{
	// if the entity cannot collide or is 100% dead, we avoid
	// solving possible collisions
	if(!collidable || dead)
		return;

    // get collisions
    QList<QGraphicsItem*> colliding_items = collidingItems();

	// will be set to true if we collide an impenetrable object
	bool revert = false;	

    // manage collisions
	for (auto& ci : colliding_items)
	{
		// convert to game object, and skip if conversion
		// does not work (should never happen)
		Object* obj = dynamic_cast<Object*>(ci);

		if (!obj)
			continue;

		// ignore collision if obj is not collidable
		if (!obj->isCollidable())
			continue;

		// get collision direction
		Direction coll_dir = collisionDirection(obj);
		// if it is not possible to calculate it, we skip current collision
		// (e.g. this may happen if we have solved the collision earlier)
		if (!coll_dir && coll_dir != UNKNOWN)
			continue;

		if (dynamic_cast<DonutBlock*>(obj) && jumping && dynamic_cast<Mario*>(this))
			continue;

		// special case 3: collision of a dying entity with another entity
		// --> ignore
		Entity* entity_obj = dynamic_cast<Entity*>(obj);
		if (entity_obj && (dying || entity_obj->isDying()))
			continue;

		// special case 4: collision with a walkable inert object while falling
		// ---> end falling and set walkable object
		Inert* inert_obj = dynamic_cast<Inert*>(obj);

		if (coll_dir == DOWN && falling && inert_obj && inert_obj->isWalkable())
		{
			falling = false;
			falling_counter = 0;
			walkable_object = inert_obj;
		}

		// special case 5: collision with an object while jumping
		// --> end jumping
		if (coll_dir == UP && jumping)
			endJumping();

		//special case : a Leaf get stuck into an inert object ---> ignore collision
		if (dynamic_cast<Inert*>(obj) && dynamic_cast<Leaf*>(this))
			continue;

		//special case : an enemy OR a collectable is hitted by a fire ball ---> ignore collision
		if (dynamic_cast<fire_ball*>(obj) && (dynamic_cast<Enemy*>(this) || dynamic_cast<Collectable*>(this)))
			continue;

		//special case : a collectable hit a fire ball or an enemy ---> ignore collision
		if (dynamic_cast<Collectable*>(obj) && (dynamic_cast<fire_ball*>(this) || dynamic_cast<Enemy*>(this)))
			continue;
		//special case : an enemy hit a collectable
		if (dynamic_cast<Enemy*>(obj) && dynamic_cast<Collectable*>(this))
			continue;

		// the two objects hit each other

		//special case: mario tanooki statue OR mario is invulnerable after being hitted
		if (special_case)			
		{
			if (dynamic_cast<Mario*>(obj) || dynamic_cast<Enemy*>(obj))
				continue;
			
			else
			{
				obj->hit(this, inverse(coll_dir));
				this->hit(obj, coll_dir);
			}
		}
		
		else if (dynamic_cast<Koopa*>(this) && dynamic_cast<Inert*>(obj) && dynamic_cast<Koopa*>(this)->getThrownAway())
		{
			dynamic_cast<Koopa*>(this)->oneShooted();
			continue;
		}
		
		else if (dynamic_cast<Koopa*>(this) && dynamic_cast<Enemy*>(obj) && dynamic_cast<Koopa*>(this)->getThrownAway())
		{
			dynamic_cast<Koopa*>(this)->oneShooted();
			dynamic_cast<Enemy*>(obj)->oneShooted();
			continue;
		}
		
		//special case : winged goomba is hitted by an enemy
		else if (dynamic_cast<Goomba*>(obj) && dynamic_cast<Enemy*>(this))
		{
			Goomba* goomba = dynamic_cast<Goomba*>(obj);
			Koopa* koopa = dynamic_cast<Koopa*>(this);

			if (koopa)
			{
				if (goomba->getWing() && koopa->getRoll())
				{
					obj->hit(this, inverse(coll_dir));
					this->hit(obj, coll_dir);
					Sounds::instance()->play("kick");
				}
				else
					continue;
			}

			else if (goomba->getWing())
				continue;
				
		}
		
		//special case : a fire_chomper hit an enemy
		else if (dynamic_cast<Fire_chomper*>(obj) && dynamic_cast<Koopa*>(this))
		{
			if (dynamic_cast<Koopa*>(this)->getRoll())
			{
				obj->hit(this, inverse(coll_dir));
				this->hit(obj, coll_dir);
				Sounds::instance()->play("kick");
			}
			else
				continue;
		}

		else if (dynamic_cast<Fire_chomper*>(obj) && dynamic_cast<Enemy*>(this))
		{
			continue;	
		}
	
		else if ( ( (dynamic_cast<Goomba*>(this) || dynamic_cast<Fire_chomper*>(this) )
			&& special_case_2 && dynamic_cast<Enemy*>(obj)) )
		{
			continue;
		}
		
		else 
		{			
			obj->hit(this, inverse(coll_dir));
			this->hit(obj, coll_dir);
		}
		
		

        // if we ended up here, it means we have to revert
		// to the previous position (impenetrability)
		revert = true;
    }

	// revert to previous position if needed
	if(revert)
		setPos(prevPos);

	// touchdown correction
	// entity is on a walkable object but is not touching it!
	// (this occurs when entity penetrates the walkable object,
	//  in which case the 'revert' operation will put it in mid-air)
	if(revert && walkable_object && !collisionDirection(walkable_object))
	{
		// just moving down until entity touches the walkable
		while(touchingDirection(walkable_object) != DOWN)
			setY(y()+1);
	}
}

void Entity::die()
{
	// only a full living entity can die
	if(!dead)
	{
		// cannot move
		moving = false;

		// dead
		dead = true;
	}
}


