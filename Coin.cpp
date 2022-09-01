#include "Coin.h"
#include "Game.h"
#include "Point.h"

Coin::Coin(QPoint position, bool _fromSecretBox) : Entity()
{
	//textures
	//different textures for different kind of coin
	texture_box_coin[0] = Sprites::instance()->get("box-coin-0");
	texture_box_coin[1] = Sprites::instance()->get("box-coin-1");
	texture_box_coin[2] = Sprites::instance()->get("box-coin-2");
	texture_box_coin[3] = Sprites::instance()->get("box-coin-3");

	texture_coin[0]     = Sprites::instance()->get("coin-0");
	texture_coin[1]		= Sprites::instance()->get("coin-1");
	texture_coin[2]		= Sprites::instance()->get("coin-2");
	texture_coin[3]		= texture_coin[0];

	//pointers
	mario = 0;

	//set flags
	fromSecretBox = _fromSecretBox;

	//set other class variables
	collidable = false;

	//set starting pixmap, position and Z value
	if (fromSecretBox)
		setPixmap(texture_box_coin[0]);			
	else 
	{
		setPixmap(texture_coin[0]);
		falling = false;
	}	
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(1);
}

void Coin::animate()
{
	Entity::animate();

	if (fromSecretBox)
		setPixmap(texture_box_coin[(animation_counter / 5) % 4]);
	else
		setPixmap(texture_coin[(animation_counter / 5) % 4]);		
}

void Coin::advance()
{
	//different advance's procedure for different kind of coin
	if (fromSecretBox)
	{
		if (animation_counter < 28)
			setY(y() - 2);
		
		else if (animation_counter >= 28 && animation_counter < 54)
			setY(y() + 2);
		
		else
		{
			Game::instance()->sumCoin(1);
			die();
			new Point(x(), y(), 100);
		}
	}
	
	else
	{
		if(mario == 0)
			mario = Game::instance()->getMario();

		if ((mario->x() <= x() + 16 && mario->x() >= x() - 16) && 
			(mario->y() <= y() + 16 && mario->y() >= y() - 16))
		{
			Sounds::instance()->play("coin");
			Game::instance()->sumCoin(1);
			new Point(x(), y(), 100);
			die();	
		}
	}		
}

