#pragma once

#include "Inert.h"
#include "Mario.h"
#include "Sprites.h"
#include "Object.h"
#include "Sounds.h"
#include "Coin.h"
#include "Mushroom.h"
#include "Leaf.h"
#include "Tanooki.h"

enum spawnable_type
{
	COIN,
	MUSHROOM,
	LEAF,
	FLOWER,
	STAR,
	TANOOKI
};

class SecretBox : public Inert
{
protected:
	QPixmap texture_active[4];
	QPixmap texture_inactive;
	QPixmap texture_big_active;
	QPixmap texture_big_inactive;

	Mario* mario;

	spawnable_type content;

	bool active;
	bool big;						//big secret box (secret room only)

	int hit_counter;
	int animation_counter;

public:
	SecretBox(QPoint position, spawnable_type spawnable = COIN, bool _big = false);

	virtual std::string name() { return "SecretBox"; }

	virtual void animate();
	virtual void hit(Object* what, Direction fromDir);
	virtual void advance();
};
