#include "Hud.h"
#include "Sprites.h"
#include <QPainter>
#include "Game.h"
#include <iostream>
#include "Card.h"

Hud::Hud(const QPoint & position)
{
	//set flags
	max_speed = false;

	//set counter
	max_speed_counter = 0;

	//set coin
	coinI = 0;
	coinJ = 0;

	//set life
	lifeI = 4;
	lifeJ = 0;

	//set point
	point1 = 0;
	point2 = 0;
	point3 = 0;
	point4 = 0;
	point5 = 0;
	point6 = 0;
	point7 = 0;

	//set roulette card
	card_hud[0] = -1;
	card_hud[1] = -1;
	card_hud[2] = -1;

	//set countdown
	time1 = 1;
	time2 = 0;
	time3 = 3;

	//set position
	setPos(position);
}

void Hud::animate() 
{
	animation_counter++;

	QPixmap collage(16 * 16 + 4, 3 * 16);
	QPainter painter(&collage);

	painter.fillRect(collage.rect(), Qt::black);
	painter.drawPixmap(10, 5, Sprites::instance()->get("hud"));

	//set pixmap of world number
	painter.drawPixmap(47.5, 12, Sprites::instance()->get("number-5"));

	if (Game::instance()->getGotCoin())
	{
		coinI++;
		//when the value of the units exceeds ten this is increased 
		if (coinI == 10)
		{
			coinJ++;
			
			//when the value of the tens exceeds 99 a life is added
			if (coinJ == 10)
			{
				coinJ = 0;
				lifeI++;
			}
			
			coinI = 0;
		}

		Game::instance()->setGotCoin(false);
		Game::instance()->setHud(this);
	}

	//set pixmap of coins
	painter.drawPixmap(142, 12, Sprites::instance()->get(vector[coinJ]));
	painter.drawPixmap(150, 12, Sprites::instance()->get(vector[coinI]));

	//set pixmap of lifes
	if (coinJ >0)
		painter.drawPixmap(39, 20, Sprites::instance()->get(vector[lifeJ]));
	painter.drawPixmap(47, 20, Sprites::instance()->get(vector[lifeI]));

	painter.drawPixmap(14, 20, Sprites::instance()->get("mario"));

	int temp_point = Game::instance()->getGotPoints();

	//calculation of points if 100 points have been received
	if (temp_point == 100)
	{
		point5++;
		
		if (point5 == 10)
		{
			point5 = 0;
			point4++;
			
			if (point4 == 10)
			{
				point4 = 0;
				point3++;
				
				if (point3 == 10)
				{
					point3 = 0;
					point2++;
					
					if (point2 == 10)
					{
						point2 = 0;
						point1++;
						
						if (point1 == 10)
						{
							point1 = 9;
							point2 = 9;
							point3 = 9;
							point4 = 9;
							point5 = 9;
							point6 = 9;
							point7 = 9;

						}
					}
				}
			}
		}
	}
	
	//calculation of points if 200 points have been received
	else if (temp_point == 200)
	{
		point5 = point5 + 2;
		
		if (point5 >= 10)
		{

			if (point5 == 11)
			{
				point5 = 1;
				point4++;
			}
			
			else
			{
				point5 = 0;
				point4++;
			}
			
			if (point4 == 10)
			{
				point4 = 0;
				point3++;
				
				if (point3 == 10)
				{
					point3 = 0;
					point2++;
					
					if (point2 == 10)
					{
						point2 = 0;
						point1++;
						
						if (point1 == 10)
						{
							point1 = 9;
							point2 = 9;
							point3 = 9;
							point4 = 9;
							point5 = 9;
							point6 = 9;
							point7 = 9;

						}
					}
				}
			}
		}
	}

	//calculation of points if 1000 points have been received
	else if (temp_point == 1000)
	{
		point4++;
		
		if (point4 == 10)
		{
			point4 = 0;
			point3++;
			
			if (point3 == 10)
			{
				point3 = 0;
				point2++;
				
				if (point2 == 10)
				{
					point2 = 0;
					point1++;
					
					if (point1 == 10)
					{
						point1 = 9;
						point2 = 9;
						point3 = 9;
						point4 = 9;
						point5 = 9;
						point6 = 9;
						point7 = 9;

					}
				}
			}
		}
	}
	
	//set pixmap of points
	painter.drawPixmap(65, 20, Sprites::instance()->get(vector[point1]));
	painter.drawPixmap(72, 20, Sprites::instance()->get(vector[point2]));
	painter.drawPixmap(79, 20, Sprites::instance()->get(vector[point3]));
	painter.drawPixmap(86, 20, Sprites::instance()->get(vector[point4]));
	painter.drawPixmap(93, 20, Sprites::instance()->get(vector[point5]));
	painter.drawPixmap(100, 20, Sprites::instance()->get(vector[point6]));
	painter.drawPixmap(107, 20, Sprites::instance()->get(vector[point7]));

	//if Mario at the end of the level has no card, the selected 
	//one is added to the first position
	if (card_hud[0] != -1)
	{
		if(card_hud[0] == 0)
			painter.drawPixmap(170, 5, Sprites::instance()->get("star-hud"));
		
		else if(card_hud[0] == 1)
			painter.drawPixmap(170, 5, Sprites::instance()->get("flower-hud"));
		
		else if(card_hud[0] == 2)
			painter.drawPixmap(170, 5, Sprites::instance()->get("mushroom-hud"));
	}
	
	//if Mario has a card at the end of the level, the selected one 
	//is added to the second position
	else if (card_hud[1] != -1)
	{
		if (card_hud[1] == 0)
			painter.drawPixmap(194, 5, Sprites::instance()->get("star-hud"));
		
		else if (card_hud[1] == 1)
			painter.drawPixmap(194, 5, Sprites::instance()->get("flower-hud"));
		
		else if (card_hud[1] == 2)
			painter.drawPixmap(194, 5, Sprites::instance()->get("mushroom-hud"));
	}
	
	//if Mario has two cards at the end of the level, the selected one 
	//is added to the third position
	else if (card_hud[2] != -1)
	{
		if (card_hud[2] == 0)
			painter.drawPixmap(218, 5, Sprites::instance()->get("star-hud"));
		
		else if (card_hud[2] == 1)
			painter.drawPixmap(218, 5, Sprites::instance()->get("flower-hud"));
		
		else if (card_hud[2] == 2)
			painter.drawPixmap(218, 5, Sprites::instance()->get("mushroom-hud"));
	}
		
	time1 = Game::instance()->getTime1();
	time2 = Game::instance()->getTime2();
	time3 = Game::instance()->getTime3();
	
	//set pixmap of countdown
	painter.drawPixmap(134, 20, Sprites::instance()->get(vector[time3]));
	painter.drawPixmap(142, 20, Sprites::instance()->get(vector[time2]));
	painter.drawPixmap(150, 20, Sprites::instance()->get(vector[time1]));

	//if Mario has reached the maximum speed set max_speed pixmap
	if (max_speed)
	{
		max_speed_counter++;
		
		if (max_speed_counter <= 20)
			painter.drawPixmap(111, 12, Sprites::instance()->get("max-speed"));
		
		else if(max_speed_counter == 40)
			max_speed_counter = 0;
	}
	
	else
		max_speed_counter = 0;

	//set the arrows according to the speed of mario
	if (speed > 225 && speed <= 250)
	{
		painter.drawPixmap(62, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(70, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(78, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(86, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(94, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(102, 12, Sprites::instance()->get("arrow"));
	}
		
	if (speed > 200 && speed <= 225)
	{
		painter.drawPixmap(62, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(70, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(78, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(86, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(94, 12, Sprites::instance()->get("arrow"));

	}
		
	if (speed > 150 && speed <= 200)
	{
		painter.drawPixmap(62, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(70, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(78, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(86, 12, Sprites::instance()->get("arrow"));
	}
		
	if (speed > 100 && speed <= 150)
	{
		painter.drawPixmap(62, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(70, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(78, 12, Sprites::instance()->get("arrow"));
	}
		
	if (speed > 75 && speed <= 100)
	{
		painter.drawPixmap(62, 12, Sprites::instance()->get("arrow"));
		painter.drawPixmap(70, 12, Sprites::instance()->get("arrow"));
	}
		
	if (speed >= 50 && speed <= 75)
		painter.drawPixmap(62, 12, Sprites::instance()->get("arrow"));

	painter.end();

	setPixmap(collage);

	setZValue(7);
}

void Hud::setCard(int _card)
{
	
	if (card_hud[0] == -1) 
		card_hud[0] = _card;
		
	if (card_hud[1] == -1)
		card_hud[1] = _card;
		
	if (card_hud[2] == -1) 
		card_hud[2] = _card;
}

void Hud::SetPointIndex(int _1, int _2, int _3, int _4, int _5, int _6, int _7)
{
	point1 = _1;
	point2 = _2;
	point3 = _3;
	point4 = _4;
	point5 = _5;
	point6 = _6;
	point7 = _7;
}