#include "Enemy.h"
#include "Game.h"

Enemy::Enemy()
{
	//set flag
	mario = 0;

	//set other class variables
	freezed = false;
	one_shooted = false;
	range = 128;
	moving_div = 5;


}

bool Enemy::disable(int _range)
{
	//if an enemy isn't within this range, it's disabled
	if (mario->x() > x() + _range || mario->x() < x() - _range)
		return true;
	else
		return false;
}
