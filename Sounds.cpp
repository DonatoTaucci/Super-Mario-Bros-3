#include "Sounds.h"

Sounds* Sounds::instance()
{
	static Sounds uniqueInstance;
	return &uniqueInstance;
}

Sounds::Sounds()
{

	sounds["1up"]		   = new QSound(":/sounds/1up.wav");
	sounds["break"]		   = new QSound(":/sounds/break.wav");
	sounds["bump"]		   = new QSound(":/sounds/bump.wav");
	sounds["cannon"]	   = new QSound(":/sounds/cannon.wav");
	sounds["coin"]		   = new QSound(":/sounds/coin.wav");
	sounds["death"]		   = new QSound(":/sounds/death.wav");
	sounds["fireball"]	   = new QSound(":/sounds/fireball.wav");
	sounds["fly"]		   = new QSound(":/sounds/fly.wav");
	sounds["gameover"]	   = new QSound(":/sounds/gameover.wav");
	sounds["jump"]		   = new QSound(":/sounds/jump.wav");
	sounds["levelend"]	   = new QSound(":/sounds/level_clear.wav");
	sounds["spawn"]		   = new QSound(":/sounds/mushroom-appear.wav");
	sounds["eat"]		   = new QSound(":/sounds/mushroom-eat.wav");
	sounds["oneup"]		   = new QSound(":/sounds/oneup.wav");
	sounds["pause"]		   = new QSound(":/sounds/pause.wav");
	sounds["pickabox"]	   = new QSound(":/sounds/pickabox.wav");
	sounds["pipe"]		   = new QSound(":/sounds/pipe-travel.wav");
	sounds["star"]		   = new QSound(":/sounds/starmusic.wav");
	sounds["stomp"]		   = new QSound(":/sounds/stomp.wav");
	sounds["tail"]		   = new QSound(":/sounds/tail.wav");
	sounds["vine"]		   = new QSound(":/sounds/vine.wav");
	sounds["kick"]		   = new QSound(":/sounds/kick.wav");
	sounds["raccoon"] 	   = new QSound(":/sounds/raccoon_transform.wav");
}

void Sounds::play(const std::string& id)
{
	if (sounds.find(id) != sounds.end())
		sounds[id]->play();
}

void Sounds::stop(const std::string& id)
{
	if (sounds.find(id) != sounds.end())
		sounds[id]->stop();
}