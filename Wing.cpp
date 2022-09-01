#include "Wing.h"
#include "Game.h"

Wing::Wing(QPoint pos, Goomba* _goomba_w, Koopa* _koopa_w, bool isGoomba, bool _reverse)
{
	//textures
	texture_wing[0] = Sprites::instance()->get("wing-0");
	texture_wing[1] = Sprites::instance()->get("wing-1");
	
	//set flags
	goomba_w = _goomba_w;
	koopa_w = _koopa_w;
	reverse = _reverse;
	slow = false;
	fast = false;
	fall = false;
	
	//set class variables
	collidable = false;
	falling = false;

	//set counter
	flyng_counter = 0;
	animation_wing = 0;
	
	//set starting pixmap, position and Z valie
	if(!reverse)
		setPixmap(texture_wing[0]);
	else
		setPixmap(texture_wing[0].transformed(QTransform().scale(-1, 1)));

	setPos(pos - QPoint(-0.5 * 16, pixmap().height() + 0.5 * 16));
	if (isGoomba)
		new Wing(pos - QPoint(0.75 * 16, 0), _goomba_w, 0, false, true);

		setZValue(2);
}

void Wing::advance()
{
	if (koopa_w != 0)
	{
		if (!koopa_w->getWing())
			die();
		
		//follow koopa's movements
		setX(koopa_w->x() + 0.25 * 16);
		setY(koopa_w->y());
	}
	
	else
	{
		if (!goomba_w->getWing())
			die();
		
		slow = goomba_w->getSlow();
		fast = goomba_w->getFast();
		fall = goomba_w->getFalling();
		
		//follow goomba's movements
		if (reverse)
		{
			setX(goomba_w->x() - 0.15 * 16);
			setY(goomba_w->y() - 0.30 * 16);
		}
		else
		{
			setX(goomba_w->x() + 0.65 * 16);
			setY(goomba_w->y() - 0.30 * 16);
		}		
	}
}

void Wing::animate()
{
	if (freezed)
		return;
	
	animation_wing++;

	if (goomba_w != 0)
	{
		if (slow)
		{
			if (!reverse)
				setPixmap(texture_wing[(animation_wing / 15) % 2]);
			
			else
				setPixmap(texture_wing[(animation_wing / 15) % 2].transformed(QTransform().scale(-1, 1)));
		}
		
		else if (fast)
		{
			if (!reverse)
				setPixmap(texture_wing[(animation_wing / 4) % 2]);
			
			else
				setPixmap(texture_wing[(animation_wing / 4) % 2].transformed(QTransform().scale(-1, 1)));
		}
		
		else if (!fast && !slow && !fall)
		{
			if (!reverse)
				setPixmap(texture_wing[1]);
			
			else
				setPixmap(texture_wing[1].transformed(QTransform().scale(-1, 1)));
		}
	
		else if (fall)
			if (!reverse)
				setPixmap(texture_wing[0]);
			
			else
				setPixmap(texture_wing[0].transformed(QTransform().scale(-1, 1)));
	}
	
	else
	{
		if(koopa_w->getDirection() == RIGHT)
			setPixmap(texture_wing[(animation_wing / 8) % 2].transformed(QTransform().scale(-1, 1)));
		
		else if(koopa_w->getDirection() == LEFT)
			setPixmap(texture_wing[(animation_wing / 8) % 2]);
	}
}
