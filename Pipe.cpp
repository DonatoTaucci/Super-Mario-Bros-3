#include "Pipe.h"
#include "Sprites.h"
#include "LevelManager.h"
#include <QPainter>
#include "Game.h"



Pipe::Pipe(QPoint position, int height, bool _upsidedown, bool _entry, bool _gray) : Inert()
{
	//pointers
	mario_p = 0;

	//set flags
	in_the_pipe = false;
	hitted = false;
	gray = _gray;
	entry = _entry;
	upsidedown = _upsidedown;

	//set other class variables
	posX = position.x();

	// create collage texture
	QPixmap collage(32, (1 + height) * 16);
	QPainter painter(&collage);

	// entrance
	if (!gray)
	{
		painter.drawPixmap(0, 0, Sprites::instance()->get("pipe-NW"));
		painter.drawPixmap(16, 0, Sprites::instance()->get("pipe-NE"));
		// pipe
		for (int i = 1; i <= height; i++)
		{
			painter.drawPixmap(0, i * 16, Sprites::instance()->get("pipe-W"));
			painter.drawPixmap(16, i * 16, Sprites::instance()->get("pipe-E"));
		}
	}
	else
	{
		painter.drawPixmap(0, 0, Sprites::instance()->get("pipe-NW-gray"));
		painter.drawPixmap(16, 0, Sprites::instance()->get("pipe-NE-gray"));
		// pipe
		for (int i = 1; i <= height; i++)
		{
			painter.drawPixmap(0, i * 16, Sprites::instance()->get("pipe-W-gray"));
			painter.drawPixmap(16, i * 16, Sprites::instance()->get("pipe-E-gray"));
		}
	}

	// end painting (necessary for setMask)
	painter.end();

	// make background color (224, 163, 216) transparent
	collage.setMask(collage.createMaskFromColor(QColor(224, 163, 216)));

	if (!_upsidedown)
		setPixmap(collage);

	else
		setPixmap(collage.transformed(QTransform().scale(1, -1)));

	// set position
	setPos(QPoint(position.x(), position.y() - (1 + height) * 16));
	setZValue(3);
}

void Pipe::hit(Object* what, Direction fromDir)
{
	if (mario_p && entry && upsidedown)
		hitted = true;

	Object::hit(what, fromDir);
}

void Pipe::advance()
{
	if (entry == true)
	{
		if (mario_p == 0)
			mario_p = Game::instance()->getMario();

		if (!upsidedown)
		{
			//enter the pipe and change scene
			if ((mario_p->x() > x() && mario_p->x() < x() + 2 * 16 && mario_p->getCrouch() == true) || in_the_pipe)
			{
				if (!in_the_pipe)
				{
					mario_p->setUpDown(true);
					mario_p->setPipeCounter(0);
					in_the_pipe = true;
				}
				
				if (mario_p->getPipeCounter() == 75)
				{
					mario_p->setChange_scene(true);
					Game::instance()->setFreezed(false);
					mario_p->setPipeCounter(-1);
				}
			}
		}
		else
		{
			//enter the pipe and change scene
			if (mario_p->x() > x() && mario_p->x() < x() + 2 * 16 && hitted)
			{
				if (!in_the_pipe)
				{
					mario_p->setUpDown(false);
					mario_p->setPipeCounter(0);
					in_the_pipe = true;
				}

				if (mario_p->getPipeCounter() == 75)
				{
					mario_p->setChange_scene(true);
					Game::instance()->setFreezed(false);
					mario_p->setPipeCounter(-1);
					hitted = false;
				}
			}
		}
	}
}