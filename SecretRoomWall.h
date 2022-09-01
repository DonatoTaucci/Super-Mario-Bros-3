#pragma once

#include "Inert.h"
#include "Sprites.h"

class SecretRoomWall : public Inert
{
protected:

	QPixmap texture;				//secret room only

public:
	SecretRoomWall(QPoint position);

	virtual std::string name() { return "SecretRoomWall"; }

	virtual void hit(Object* what, Direction fromDir);
};
