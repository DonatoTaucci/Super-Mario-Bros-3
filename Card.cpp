#include "Card.h"
#include "Mario.h"
#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"


Card::Card(QPoint position) 
{
	//textures
	block[0] = Sprites::instance()->get("roulette-0");
	block[1] = Sprites::instance()->get("roulette-1");
	block[2] = Sprites::instance()->get("roulette-2");
	star[0] = Sprites::instance()->get("star-0");
	star[1] = Sprites::instance()->get("star-1");
	star[2] = Sprites::instance()->get("star-2");
	flower[0] = Sprites::instance()->get("flower-0");
	flower[1] = Sprites::instance()->get("flower-1");
	flower[2] = Sprites::instance()->get("flower-2");
	mushroom[0] = Sprites::instance()->get("mushroom-0");
	mushroom[1] = Sprites::instance()->get("mushroom-1");
	mushroom[2] = Sprites::instance()->get("mushroom-2");

	//set flags
	hitted = false;
	
	//set class variables
	collidable = true;
	moving_speed_div = 8;

	//set starting pixmap, position, Z value
	setPixmap(block[0]);
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(3);
}

void Card::advance()
{
	if (hitted == true)
		setY(y() - 1);
};


void Card::animate()
{
	Entity::animate();

	if (hitted == false)
	{
		setPixmap(block[(animation_counter / 8) % 3]);
		selected_card = (animation_counter / 8) % 3;
	}

	if (hitted == true)
	{
		if (selected_card == 0)
			setPixmap(star[(animation_counter / 12) % 3]);

		else if (selected_card == 1)
			setPixmap(flower[(animation_counter / 12) % 3]);

		else if (selected_card == 2)
			setPixmap(mushroom[(animation_counter / 12) % 3]);
	}
}


void Card::hit(Object* what, Direction fromDir) 
{
	Object::hit(what, fromDir);

	if (dynamic_cast<Mario*>(what))
	{
		hitted = true;
		Game::instance()->setFinish(true);				//the game's finish procedure starts
		Game::instance()->setCard(selected_card);
	}
};



