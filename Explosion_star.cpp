#include "Explosion_star.h"


Explosion_star::Explosion_star(QPoint position, int _number, int _dirX, int _dirY, int _counter)
{
	//texture
	texture_star[0] = Sprites::instance()->get("green-star");
	texture_star[1] = Sprites::instance()->get("yellow-star");
	texture_star[2] = Sprites::instance()->get("black-star");
	texture_star[3] = Sprites::instance()->get("red-star");

	

	//other class variables
	collidable = false;
	moving_counter = 0;
	counter = _counter;
	number = _number;
	pos = position;
	dirX = _dirX;	
	dirY = _dirY;	

	//set starting Pixmap
	setPixmap(texture_star[0]);

	//set a different starting position based on the number value
	if(number == 1)
		setPos(QPoint(pos.x() + 4, pos.y() - 6));
	else if (number == 2)
		setPos(QPoint(pos.x() + 7, pos.y()));
	else if (number == 3)
		setPos(QPoint(pos.x() + 4, pos.y() + 6));
	else if (number == 4)
		setPos(QPoint(pos.x() -4, pos.y() + 6));
	else if (number == 5)
		setPos(QPoint(pos.x() - 7, pos.y()));
	else if (number == 6)
		setPos(QPoint(pos.x() -4, pos.y() - 6));

	else if (number == 7)
		setPos(QPoint(pos.x(), pos.y() - 6));
	else if (number == 8)
		setPos(QPoint(pos.x() + 8, pos.y()));
	else if (number == 9)
		setPos(QPoint(pos.x() + 8, pos.y() + 8));
	else if (number == 10)
		setPos(QPoint(pos.x(), pos.y() + 12));
	else if (number == 11)
		setPos(QPoint(pos.x() - 8, pos.y() + 8));
	else if (number == 12)
		setPos(QPoint(pos.x() - 8, pos.y()));

	//set Z value
	setZValue(4);
}

void Explosion_star::advance()
{
	moving_counter++;

	if (moving_counter == 10)
	{
		if (counter <= 5)
		{
			setPos(pos);		//place the object in the starting spawn space													


			if (number <= 6)
			{
				//second formation
				number = number + 6;

				if (number == 7)
					new Explosion_star(QPoint(x(), y()), 7, 0, -2, counter + 1);
				else if (number == 8)
					new Explosion_star(QPoint(x(), y()), 8, 2, -1, counter + 1);
				else if (number == 9)
					new Explosion_star(QPoint(x(), y()), 9, 2, 1, counter + 1);
				else if (number == 10)
					new Explosion_star(QPoint(x(), y()), 10, 0, 2, counter + 1);
				else if (number == 11)
					new Explosion_star(QPoint(x(), y()), 11, -2, 1, counter + 1);
				else if (number == 12)
					new Explosion_star(QPoint(x(), y()), 12, -2, -1, counter + 1);
			}
			
			else if (number > 6)
			{
				//first formation 
				number = number - 6;

				if (number == 1)
					new Explosion_star(QPoint(x(), y()), 1, 1, -2, counter + 1);
				else if (number == 2)
					new Explosion_star(QPoint(x(), y()), 2, 2, 0, counter + 1);
				else if (number == 3)
					new Explosion_star(QPoint(x(), y()), 3, 1, 2, counter + 1);
				else if (number == 4)
					new Explosion_star(QPoint(x(), y()), 4, -1, 2, counter + 1);
				else if (number == 5)
					new Explosion_star(QPoint(x(), y()), 5, -2, 0, counter + 1);
				else if (number == 6)
					new Explosion_star(QPoint(x(), y()), 6, -1, -2, counter + 1);
			}
			
			moving_counter = 0;
		}

		die();
	}
		
	setX(x() + dirX);
	setY(y() + dirY);
}

void Explosion_star::animate()
{
	setPixmap(texture_star[(moving_counter / 6) % 4]);
}