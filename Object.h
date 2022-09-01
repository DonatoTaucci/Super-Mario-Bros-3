#pragma once

#include <string>
#include <QGraphicsPixmapItem>
#include "utils.h"

// base class for all game objects
class Object : public QGraphicsPixmapItem
{	
	protected:

		bool collidable;					// whether the object is collidable
		bool collider_visible;				// whether the collider is visible

	public:

		Object();

		virtual std::string name() = 0;
        virtual void animate() = 0;
        virtual void advance() = 0;
        virtual void solveCollisions() = 0;
		virtual void hit(Object *what, Direction fromDir) = 0;

        virtual Direction collisionDirection(Object* item);
        virtual Direction touchingDirection(Object* item);
		bool isCollidable() { return collidable; }
		void toogleColliderVisible();
};
