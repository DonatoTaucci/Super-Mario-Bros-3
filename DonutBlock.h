#pragma once

#include "Inert.h"
#include "Mario.h"
#include "Sprites.h"
#include "Game.h"


class DonutBlock : public Inert
{
protected:
	QPixmap texture_DonutBlock;
	QPixmap texture_shake[4];

	Mario* mario_d;

	bool touched;
	bool freezed;

	int touch_counter;
	int animation_counter;
	int posX;
	int posY;
	



public:
	DonutBlock(QPoint position, Mario* mario);

	virtual std::string name() { return "DonutBlock"; }
	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir);
	virtual void setFreezed(bool _freezed) { freezed = _freezed; }

	QPainterPath shape() const ;	
};
