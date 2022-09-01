#include "Brick.h"
#include "Mario.h"
#include "BrickDebris.h"
#include "Koopa.h"
#include <QSound>

Brick::Brick(QPoint position, bool _drop, spawnable_type _content) : Inert()
{

	//textures
	texture_brick[0] = Sprites::instance()->get("brick");
	texture_brick[1] = Sprites::instance()->get("brick-1");
	texture_brick[2] = Sprites::instance()->get("brick-2");
	texture_brick[3] = Sprites::instance()->get("brick-3");
	texture_inactive = Sprites::instance()->get("secret-box-inactive");

	//set spawnable type
	content = _content;

	//pointers
	mario_b = 0;

	//set flag
	drop = _drop;
	active = drop;
	broken = false;
	skip = false;

	//set counter
	hit_counter = -1;
	animation_counter = 0;

	//set other class variables
	hit_duration = 10;

	//set starting pixmap, position, Z value
	setPixmap(texture_brick[1]);
	setPos(position);
	setZValue(2);
}


void Brick::advance()
{
	if(mario_b == 0)
		mario_b = Game::instance()->getMario();

	if (!drop)
	{
		if ((x() < mario_b->x() + 2 * 16) && x() > mario_b->x() - 2 * 16 && ((y() > mario_b->y()) &&
			(y() < mario_b->y() + 32)) && mario_b->isSpinning() && !broken && !skip)
		{
			broken = true;
			skip = true;							//variable used in order not to generate multiple
													//objects of the BrickDebris class than desired	
		}
	}

	if (hit_counter >= 0)
	{
		if (hit_counter < 12)
		{
			setY(y() - 1);
			hit_counter++;
		}

		if (hit_counter >= 12 && hit_counter < 24)
		{
			setY(y() + 1);
			hit_counter++;
		}

		if (hit_counter == 24)
			hit_counter = -1;
	}

	if (broken)
	{
		QSound::play(":/sounds/break.wav");
		setVisible(false);

		new BrickDebris(pos() + QPoint(0, -4), LEFT);
		new BrickDebris(pos() + QPoint(0, 12), LEFT);
		new BrickDebris(pos() + QPoint(16, -4), RIGHT);
		new BrickDebris(pos() + QPoint(16, 12), RIGHT);

		broken = false;
	}
}

void Brick::animate()
{
	if (!active && drop)
		setPixmap(texture_inactive);
	else
	{
		animation_counter++;
		setPixmap(texture_brick[(animation_counter / 10) % 4]);
	}
}

void Brick::hit(Object* what, Direction fromDir)
{
	Mario* mario_b = dynamic_cast<Mario*>(what);
	if (mario_b && fromDir == DOWN)
	{
		if (active)
		{
			hit_counter = 0;
			active = false;
			Sounds::instance()->play("bump");

			if (content == COIN)
				new Coin(QPoint(x(), y()));
			else if (content == LEAF)
			{
				if (mario_b->isBig())
					new Leaf(QPoint(x(), y()));
			
				else
					new Mushroom(QPoint(x(), y()));
			}
		}
		
		else if (mario_b->isBig() && !drop)
			broken = true;
		
		else if(!drop)
		{
			QSound::play(":/sounds/bump.wav");
			hit_counter = 0;
		}
		
		else if (drop)
				QSound::play(":/sounds/bump.wav");
	}

	if (dynamic_cast<Koopa*>(what) && (fromDir == RIGHT || fromDir == LEFT))
		broken = true;

	return;
}

