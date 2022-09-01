#include "TigerBlock.h"


TigerBlock::TigerBlock(QPoint position,bool _drop, spawnable_type spawnable) : Inert()
{
	// textures
	texture_tiger_block = Sprites::instance()->get("tiger-block");
	texture_inactive = Sprites::instance()->get("secret-box-inactive");

	//pointers
	mario = 0;

	// set flags
	drop = _drop;
	moving = _drop;
	content = spawnable;

	// set counters
	hit_counter_L= -1;
	hit_counter_R = -1;

	// set starting pixmap, position and Z value
	setPixmap(texture_tiger_block);
	setPos(position - QPoint(0, pixmap().height()));
	setZValue(3);
}

void TigerBlock::advance()
{
	if(mario == 0)
		mario = Game::instance()->getMario();
	
	if (hit_counter_L >= 0)
	{
		if (hit_counter_L == 1)
			Sounds::instance()->play("bump");

		//mario won't stuck into the tiger block
		if (mario->x() < x() && mario->x() > x() - 16)
		{
			if (mario->isRunning())
				mario->setX(mario->x() - 6);

			else
				mario->setX(mario->x() - 4);
		}

		//if has been hitted from the LEFT, move the tiger block to the RIGHT
		if (hit_counter_L < 12)
		{
			setX(x() + 1);
			hit_counter_L++;
		}
		
		if (hit_counter_L >= 12 && hit_counter_L < 24)
		{
			setX(x() - 1);
			hit_counter_L++;
		}
		
		if(hit_counter_L >= 24)
			hit_counter_L = -1;
	}

	else if (hit_counter_R >= 0)
	{
		if (hit_counter_R == 1)
			Sounds::instance()->play("bump");

		//mario won't stuck into the tiger block
		if (mario->x() > x() && mario->x() < x() + 16)
		{
			if (mario->isRunning())
				mario->setX(mario->x() + 6);

			else
				mario->setX(mario->x() + 4);
		}

		//if has been hitted from the LEFT, move the tiger block to the RIGHT
		if (hit_counter_R < 12)
		{
			setX(x() - 1);
			hit_counter_R++;
		}
		
		if (hit_counter_R >= 12 && hit_counter_R < 24)
		{
			setX(x() + 1);
			hit_counter_R++;
		}
		
		if (hit_counter_R >= 24)
			hit_counter_R = -1;
	}
}

void TigerBlock::hit(Object* what, Direction fromDir)
{
	Mario* mario_t;
	mario_t = dynamic_cast<Mario*>(what);

	if (hit_counter_L >= 0 || hit_counter_R >= 0)
		return;

	if (mario_t && (fromDir == LEFT))
	{
		
		if (moving)
		{
			hit_counter_L = 0;
			if (drop)
			{
				drop = false;
				setPixmap(texture_inactive);
				Sounds::instance()->play("bump");
				
				if (content == COIN)
					new Coin(QPoint(x(), y()));
				
				else if (content == LEAF)
				{
					if (mario->isBig())
						new Leaf(QPoint(x(), y()));
					
					else
					{
						Sounds::instance()->play("spawn");
						new Mushroom(QPoint(x(), y()));
					}
				}
			}
		}
	}
	else if (mario_t && (fromDir == RIGHT))
	{
		if (moving)
		{
			hit_counter_R = 0;
			if (drop)
			{
				drop = false;
				setPixmap(texture_inactive);
				Sounds::instance()->play("bump");
			
				if (content == COIN)
					new Coin(QPoint(x(), y()));
				
				else if (content == LEAF)
				{
					if (mario->isBig())
						new Leaf(QPoint(x(), y()));
					
					else
						new Mushroom(QPoint(x(), y()));
				}
			}
		}
	}
}
	

