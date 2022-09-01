#pragma once

#include "Enemy.h"
#include "Sprites.h"
#include "Game.h"
#include "Fire_ball.h"

class Plant : public Enemy
{
protected:
	QPixmap texture_fireplant[4];
	QPixmap texture_cloud[4];
	QPixmap texture_biteplant[2];

	QPoint pos;

	bool notmove;
	bool upsidedown;
	bool mouth;				//set shooting texture
	bool done;				//true if the fire plant has already shooted
	bool fire_plant;		//false ---> bite plant 
							//true  ---> fire plant

	int pause;				//pause between the 2 movement : up and down
	int advance_counter;
	int tex;				//texture index

public:
	Plant(QPoint position, Direction direction = LEFT, bool _upsidedown = false, bool _type = true);

	virtual std::string name() { return "Plants"; }

	virtual void animate();
	virtual void advance();
	virtual void hit(Object* what, Direction fromDir) {};
	virtual void hurt();

	void shoot();
};