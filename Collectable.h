#pragma once

#include "Entity.h"

class Collectable : public Entity
{
	protected:

		QPoint spawned_position;	// position where collectable spawned

	public:

		Collectable(QPoint position);

		// inherited methods
		virtual std::string name() = 0;
		virtual void animate() = 0;
		virtual void hit(Object *what, Direction fromDir) = 0;
};