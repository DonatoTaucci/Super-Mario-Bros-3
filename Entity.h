#pragma once

#include "Inert.h"

// Entity object are "living", i.e. they can move, animate, fall,
// jump, collide, die, etc.
class Entity : public Object
{
    protected:
		QPointF prevPos;                    // previous position
		Direction dir;						// the direction of movement

		Inert* walkable_object;				// inert on which current entity is walking

		//flags
		bool moving;						// is moving?
		bool jumping;						// is jumping?
		bool falling;						// is falling (gravity)?
		bool dying;							// is dying
		bool dead;							// is dead?
		bool freezed;
		bool slow;
		bool special_case;
		bool special_case_2;

		// physics parameters
		int moving_speed;					// moving speed (pixels/frame)
		int jumping_speed;					// jumping speed (pixels/frame)
		int falling_speed;					// falling speed (pixels/frame)
		int moving_speed_div;
		int falling_speed_div;

		// counters
		int animation_counter;				// main animation cycle
        int jump_counter;					// counts the number of frames since jump started
		int falling_counter;				// counts the number of frames since falling started
		int death_counter;					// counts the number of frames since the entity has been scheduled for death
		int moving_div_counter;
		
		// durations (= limits for counters that are time-limited)
		int jumping_duration;				// jump duration (frames)
		int death_duration;					// limit for death_counter
		
        

        // utility methods
        virtual void startJumping();
        virtual void endJumping();

    public:

        Entity();

		// getters and setters
		bool isDead(){return dead;}
		void setDead(bool _dead) { dead = _dead; }
		bool isDying(){return dying;}
		bool isFalling() {return falling;}
		virtual void setDirection(Direction _dir) { dir = _dir;}
		virtual void setMoving(bool _moving) { moving = _moving;}
		virtual void setFreezed(bool _freezed) { freezed = _freezed; }
		virtual void setJumpingDuration(int jump) { jumping_duration = jump; }

        // pure virtual methods to be implemented
        virtual std::string name()     = 0;
        virtual void animate()         = 0;
        virtual void advance();
        virtual void solveCollisions();
        virtual void hit(Object *what, Direction fromDir) = 0;
		
		// die method, performs common operations to all entities
		// but it will need be overridden in some cases
		virtual void die();
};
