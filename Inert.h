#pragma once

#include "Object.h"

// Inert objects are not animated and do not move
// (a few exceptions may apply, so we keep methods virtual)
class Inert : public Object
{
	private:

		bool walkable;

    public:

		Inert();

		bool isWalkable() { return walkable; }

        virtual std::string name() = 0;
        virtual void animate() {}
        virtual void advance() {}
		virtual void solveCollisions() {}
        virtual void hit(Object *what, Direction fromDir) = 0;
};
