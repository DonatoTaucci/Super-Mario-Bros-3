#pragma once

#include "Entity.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Mario.h"

class Coin : public Entity
{
protected:

	QPixmap texture_box_coin[4];
	QPixmap texture_coin[4];

	Mario* mario;

	bool fromSecretBox;
	

public:

	Coin(QPoint position, bool _fromSecretBox = true);

	virtual std::string name() { return "Coin"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir) {}


};