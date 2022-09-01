#pragma once

#include "Inert.h"
#include "Mario.h"
#include "Sprites.h"
#include "Object.h"
#include "Sounds.h"
#include "Collectable.h"
#include "Secret_box.h"


class TigerBlock: public Inert
{
protected:
	QPixmap texture_tiger_block;
	QPixmap texture_inactive;

	Mario* mario;

	spawnable_type content;

	bool drop;
	bool moving;

	int hit_counter_L;				//start this counter only if drop is true and 
									//has been hitted by mario from the LEFT
	int hit_counter_R;				//start this counter only if drop is true and 
									//has been hitted by mario from the RIGHT

public:
	TigerBlock(QPoint position, bool _drop = false, spawnable_type spawnable = LEAF);

	virtual std::string name() { return "TigerBlock"; }
	
	virtual void hit(Object* what, Direction fromDir);
	virtual void advance();
};

