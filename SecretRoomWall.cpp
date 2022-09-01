#include "SecretRoomWall.h"
#include "Object.h"

SecretRoomWall::SecretRoomWall(QPoint position)
{
	//texture
	texture = Sprites::instance()->get("Ice-blu");

	//set starting pixmap, position and Z value
	setPixmap(texture);
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(3);
}

void SecretRoomWall::hit(Object* what, Direction fromDir)
{
	Object::hit(what, fromDir);
}