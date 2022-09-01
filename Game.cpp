#include <QApplication>
#include <QKeyEvent>
#include <QScrollBar>
#include <QWheelEvent>
#include <QSound>
#include <QThread>
#include "Game.h"
#include "Object.h"
#include "Entity.h"
#include "Mario.h"
#include "Sounds.h"
#include "Sprites.h"
#include "Hud.h"
#include "Enemy.h"
#include "DonutBlock.h"
#include "Card.h"
#include "Finish.h"

using namespace std;

// Singleton design pattern
Game* Game::uniqueInstance = 0;
Game* Game::instance()
{
	if (uniqueInstance == 0)
		uniqueInstance = new Game();
	return uniqueInstance;
}


Game::Game(QGraphicsView* parent) : QGraphicsView(parent)
{
	// setup scene/view
	scene = new QGraphicsScene();
	setScene(scene);
	scale(3.0, 3.0);
	centerOn(0, 0);
	setInteractive(false);		// disables events
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	scene->setSceneRect(0, 0, 160 * 16, 15 * 16);

	//set flags
	moveRight = false;
	moveLeft = false;
	secret_room = true;
	back2world = false;
	finish = false;
	first_run = true;
	other_run = false;
	marioBig = false;
	marioRaccoon = false;
	marioTanooki = false;
	got_a_coin = false;
	got_points = false;

	//set counters
	finish_counter = 0;
	coin_number = 0;
	point = 0;

	// setup game engine
	QObject::connect(&engine, SIGNAL(timeout()), this, SLOT(advance()));
	engine.setInterval(15);

	// setup game music
	music = new QSound(":/sounds/overworld2.wav");
	music->setLoops(QSound::Infinite);

	max_speed = new QSound(":/sounds/fly.wav");
	max_speed->setLoops(QSound::Infinite);

	// reset game
	reset();

	// setup window size
	this->setFixedHeight(3 * 15 * 16);
	this->setFixedWidth(3 * 16 * 16);
}

// reset game
void Game::reset()
{
	if (first_run && other_run)
		first_run = false;

	if (lifeI < 0 && lifeJ == 0)
	{
		first_run = true;
		other_run = false;
		Sounds::instance()->play("gameover");
	}

	if (finish)
	{
		first_run = true;
		other_run = false;
	}

	if (first_run)
	{
		
		cur_state = READY;
		mario = 0;
		engine.stop();
		music->stop();
		scene->clear();
		grid.clear();

		finish = false;
		finish_counter = 0;

		lifeI = 4;
		lifeJ = 0;

		coinI = 0;
		coinJ = 0;

		for (int x = 0; x < 7; x++)
			pointIndex[x] = 0;

		time1 = 0;
		time2 = 0;
		time3 = 3;
		time_left = 300;
		countdown = 0;

		// display welcome message
		scene->setBackgroundBrush(QBrush(Qt::black));
		scene->addPixmap(Sprites::instance()->get("main-screen"));

		centerOn(0, 0);
	}
	
	else if (other_run)
	{
		cur_state = READY;

		coinI = hud->getCoinI();
		coinJ = hud->getCoinJ();

		time1 = 0;
		time2 = 0;
		time3 = 3;
		time_left = 300;
		countdown = 0;
		max_speed_counter = 0;

		finish = false;
		finish_counter = 0;

		pointIndex[0] = hud->getPoint1();
		pointIndex[1] = hud->getPoint2();
		pointIndex[2] = hud->getPoint3();
		pointIndex[3] = hud->getPoint4();
		pointIndex[4] = hud->getPoint5();
		pointIndex[5] = hud->getPoint6();
		pointIndex[6] = hud->getPoint7();

		engine.stop();
		music->stop();
		scene->clear();
		grid.clear();

		scene->setBackgroundBrush(QBrush(Qt::black));
		scene->addPixmap(Sprites::instance()->get("main-screen"));

		mario = 0;

		centerOn(0, 0);
	}
}

// game over
void Game::gameover()
{
	// stop game
	cur_state = GAME_OVER;
	engine.stop();

	// set black background
	scene->setBackgroundBrush(QBrush(Qt::black));
}

void Game::changeScene()
{

	mario->setChange_scene(false);

	//set the power up if mario has one 
	if (mario->isBig())
		marioBig = true;

	if (mario->isRaccoon())
		marioRaccoon = true;

	if (mario->isTanooki())
		marioTanooki = true;

	cur_state = READY;

	//set the hud as it was before entering the pipe
	coinI = hud->getCoinI();
	coinJ = hud->getCoinJ();
	lifeI = hud->getLifeI();
	lifeJ = hud->getLifeJ();
	pointIndex[0] = hud->getPoint1();
	pointIndex[1] = hud->getPoint2();
	pointIndex[2] = hud->getPoint3();
	pointIndex[3] = hud->getPoint4();
	pointIndex[4] = hud->getPoint5();
	pointIndex[5] = hud->getPoint6();
	pointIndex[6] = hud->getPoint7();

	engine.stop();
	music->stop();
	scene->clear();
	grid.clear();
	if (secret_room)
	{
		music = new QSound(":/sounds/underworld.wav");
		music->setLoops(QSound::Infinite);

		mario = LevelManager::load("Secret-room", scene, marioBig, marioRaccoon, marioTanooki);
	}
	else if (back2world)
	{
		music = new QSound(":/sounds/overworld2.wav");
		music->setLoops(QSound::Infinite);

		mario = LevelManager::load("World-1-1-pipe", scene, marioBig, marioRaccoon, marioTanooki);
	}
	centerOn(0, 0);

	other_run = false;
	first_run = false;

	start();
}

// start new game
void Game::start()
{
	if (cur_state == READY)
	{
		scene->clear();
		engine.start();


		// load level OR room
		if (other_run || first_run)
			mario = LevelManager::load("World-1-1", scene);

		else if (back2world)
		{
			back2world = false;
			secret_room = true;
			other_run = true;

			if (marioTanooki)
				marioRaccoon = false;

			mario = LevelManager::load("World-1-1-pipe", scene, marioBig, marioRaccoon, marioTanooki);
		}

		else if (secret_room)
		{
			secret_room = false;
			back2world = true;
			other_run = true;

			mario = LevelManager::load("Secret-room", scene, marioBig, marioRaccoon, marioTanooki);
		}

		// create a new hud
		if (first_run)
			hud = new Hud(QPoint(0, 12 * 16 + 1));
		
		else
		{
			//create a hud and set the current parameters
			hud = new Hud(QPoint(0, 12 * 16 + 1));
			hud->setCoin(coinI, coinJ);
			hud->setLife(lifeI, lifeJ);
			hud->SetPointIndex(pointIndex[0], pointIndex[1], pointIndex[2], pointIndex[3], pointIndex[4], pointIndex[5], pointIndex[6]);
		}

		// add debug grid
		for (int i = 0; i <= 15; i++)
			grid.push_back(new QGraphicsLineItem(0, i * 16, 176 * 16, i * 16));
		for (int j = 0; j <= 176; j++)
			grid.push_back(new QGraphicsLineItem(j * 16, 0, j * 16, 15 * 16));
		for (auto& l : grid)
		{
			l->setPen(QPen(QBrush(Qt::gray), 0.5));
			l->setZValue(100);
			scene->addItem(l);
			l->setVisible(false);
		}

		if (!mario)
		{
			scene->setBackgroundBrush(QBrush(QColor(242, 204, 204)));
			QGraphicsTextItem* text = scene->addText("Error when loading level");
			text->setPos(300, 90);
			centerOn(text);
		}
		
		else
			music->play();

		cur_state = RUNNING;
	}
}

// pause / resume game
void Game::tooglePause()
{
	if (cur_state == RUNNING)
	{
		engine.stop();
		music->stop();
		cur_state = PAUSE;
		Sounds::instance()->play("pause");
	}
	
	else if (cur_state == PAUSE)
	{
		engine.start();
		music->play();
		cur_state = RUNNING;
	}
}

// show/ hide level grid
void Game::toogleGrid()
{
	for (auto& l : grid)
		l->setVisible(!l->isVisible());
}

// show/ hide object colliders
void Game::toogleColliders()
{
	for (auto& item : scene->items())
		if (dynamic_cast<Object*>(item))
			dynamic_cast<Object*>(item)->toogleColliderVisible();
}

// stop music
void Game::stopMusic()
{
	if (music)
		music->stop();
}

void Game::keyPressEvent(QKeyEvent* e)
{

	// ignore auto repeat key pressed/released
	// (same key has been pressed before and we already processed it)
	if (e->isAutoRepeat())
		return;

	if (e->key() == Qt::Key_Space && !finish)
	{
		mario->jump();
		if ((mario->isRaccoon() || mario->isTanooki()) && mario->isFalling())
		{
			if (mario->isRunning() && mario->getRunningCounter() >= 250)
			{
				Sounds::instance()->play("tail");
				mario->setFlying(true);
			}
				
			else
			{
				Sounds::instance()->play("tail");
				mario->setGliding(true);
			}	
		}	
	}
		
	// start new game
	if (e->key() == Qt::Key_Return && cur_state == READY)
		start();

	// reset game
	if (e->key() == Qt::Key_R)
	{
		marioBig = false;
		marioTanooki = false;
		marioRaccoon = false;
		first_run = true;
		other_run = false;

		back2world = false;
		secret_room = true;

		reset();
	}

	if (cur_state == GAME_OVER)
	{
		marioBig = false;
		marioTanooki = false;
		marioRaccoon = false;
		if (lifeI > 0 || lifeJ > 0)
			other_run = true;

		reset();
	}

	// pause game
	if (e->key() == Qt::Key_P)
		tooglePause();

	// show/hide grid game
	if (e->key() == Qt::Key_G)
		toogleGrid();

	// show/hide colliders
	if (e->key() == Qt::Key_C)
		toogleColliders();

	// from now on, all commands require the game to be running
	if (cur_state != RUNNING)
		return;

	// speed up / slow down
	if (e->key() == Qt::Key_Plus)
		engine.setInterval(engine.interval() / 5);
	if (e->key() == Qt::Key_Minus)
		engine.setInterval(engine.interval() * 5);

	// horizontal Mario's movements
	if (e->key() == Qt::Key_Right && !mario->isDying() && !finish)
	{
		mario->setDirection(e->key() == Qt::Key_Right ? Direction::RIGHT : Direction::LEFT);
		mario->setMoving(true);
		moveRight = true;
		moveLeft = false;
	}

	if (e->key() == Qt::Key_Left && !mario->isDying() && !finish)
	{
		mario->setDirection(e->key() == Qt::Key_Left ? Direction::LEFT : Direction::RIGHT);
		mario->setMoving(true);
		moveRight = false;
		moveLeft = true;
	}

	if (e->key() == Qt::Key_Down)
		mario->setCrouch(true);

	if (e->key() == Qt::Key_T)
		mario->powerUp();

	if (e->key() == Qt::Key_Q)
		mario->powerUpLeaf();

	if (e->key() == Qt::Key_I)
		mario->powerUpTanooki();

	if (e->key() == Qt::Key_D)
		mario->back2small();

	// Mario's running
	if (e->key() == Qt::Key_Z)
	{
		mario->setRunning(true);

		if (mario->isRaccoon() || mario->isTanooki())
		{
			Sounds::instance()->play("tail");
			mario->setSpinning(true);
		}
			
	}

	if (mario->isTanooki() && e->key() == Qt::Key_Shift)
	{
		mario->setStatue(true);
		Sounds::instance()->play("raccoon");
	}

	// hurt every enemy
	if (e->key() == Qt::Key_H)
		for (auto& item : scene->items())
		{
			Enemy* obj = dynamic_cast<Enemy*>(item);
			if (obj)
				obj->hurt();
		}
}

void Game::keyReleaseEvent(QKeyEvent* e)
{
	// ignore auto repeat key pressed/released
	// (same key has been pressed before and we already processed it)
	if (e->isAutoRepeat())
		return;

	// from now on, all commands require the game to be running
	if (cur_state != RUNNING)
		return;

	// horizontal Mario's movements
	if (e->key() == Qt::Key_Left && moveRight == true)
		return;
	if (e->key() == Qt::Key_Right && moveLeft == true)
		return;
	if ((e->key() == Qt::Key_Right || e->key() == Qt::Key_Left))
		mario->setMoving(false);
	if (e->key() == Qt::Key_Down)
		mario->setCrouch(false);

	if (e->key() == Qt::Key_Space)
	{
		if (mario->isJumping())
			mario->setJumpingDuration(2 * 16);
	}

	// Mario's running
	if (e->key() == Qt::Key_Z)
		mario->setRunning(false);

	if (mario->isTanooki() && e->key() == Qt::Key_Shift)
	{
		if (mario->isStatue())
		{
			Sounds::instance()->play("raccoon");
			mario->setStatue(false);
			mario->setStatueCounter(4);
		}
	}
}

// zoom-in/out
void Game::wheelEvent(QWheelEvent* e)
{
	if (e->delta() > 0)
		scale(1.1, 1.1);
	else
		scale(1 / 1.1, 1 / 1.1);
}

void Game::advance()
{
	countdown++;

	if (mario->isDying())
	{
		max_speed->stop();
		music->stop();
	}
		
	//finish procedure
	if (finish)
	{
		finish_counter++;

		if (finish_counter == 1)
		{
			music->stop();
			Sounds::instance()->play("levelend");
		}
			
		if (mario->x() >= 159 * 16 && time_left > 0)
		{
			time1--;
			if (time1 == -1)
			{
				time1 = 9;
				time2--;
				if (time2 == -1)
				{
					time2 = 9;
					time3--;
					if (time3 < 0)
					{
						time1 = 0;
						time2 = 0;
						time3 = 0;
						reset();
					}
				}
			}
			time_left--;
			sumPoint(100);
		}

		if(finish_counter < 150)
		{
			//create the end game writings
			if (finish_counter == 110)
				new Finish(QPoint(149 * 16, 2 * 16), 1);
			if (finish_counter == 140)
				new Finish(QPoint(148 * 16, 3.5 * 16), 2);
			if (finish_counter == 140)
				new Finish(QPoint(155.5 * 16, 3 * 16), 3, card);

			if (card == 0)
				hud->setCard(card);

			else if (card == 1)
				hud->setCard(card);

			else if (card == 2)
				hud->setCard(card);
		}		
	}

	if (mario->getChange_scene())
		changeScene();

	// do nothing if game is not running
	if (cur_state != RUNNING)
		return;

	hud->setSpeed(mario->getRunningCounter());

	if (mario->getRunningCounter() == 250)
	{
		max_speed_counter++;
		hud->setMaxSpeed(true);
	}
	
	else
	{
		hud->setMaxSpeed(false);
		max_speed_counter = 0;
	}
		

	if (max_speed_counter == 1)
		max_speed->play();
	else if (max_speed_counter == 0)
		max_speed->stop();


	if (countdown % 60 == 0 && !finish)
	{
		time1--;

		if (time1 == -1)
		{
			time1 = 9;
			time2--;
			if (time2 == -1)
			{
				time2 = 9;
				time3--;
				if (time3 < 0)
				{
					time1 = 0;
					time2 = 0;
					time3 = 0;
				}
			}
		}
		time_left--;
	}
	if (time3 == 0 && time2 == 0 && time1 == 0 && !finish)
		gameover();

	if (mario->isDead())
		gameover();

	// hud follows the viewport
	hud->setX(-2 + mapToScene(rect()).boundingRect().left());

	// tell all game objects to animate and advance in the scene
	for (auto& item : scene->items())
	{
		Object* obj = dynamic_cast<Object*>(item);
		if (obj)
		{
			obj->animate();
			obj->advance();

			// destroy died Entity objects, except Mario
			Entity* entity_obj = dynamic_cast<Entity*>(obj);
			Mario* mario_obj = dynamic_cast<Mario*>(obj);
			if (entity_obj && !mario_obj && entity_obj->isDead())
			{
				scene->removeItem(entity_obj);
				delete entity_obj;
			}
		}
	}

	// center view on Mario
	centerOn(mario);
}


// freeze/unfreeze all entities
void Game::setFreezed(bool freezed)
{
	// tell all game objects to animate and advance in the scene
	for (auto& item : scene->items())
	{
		Entity* obj = dynamic_cast<Entity*>(item);
		if (obj)
			obj->setFreezed(freezed);

		DonutBlock* donut = dynamic_cast<DonutBlock*>(item);
		if (donut)
			donut->setFreezed(freezed);

		if (mario->isDying() || mario->isSpinning())					//spinning is controlled to avoid softlock
			mario->setFreezed(false);
	}
}

int Game::getGotPoints()
{
	if (got_points)
	{
		got_points = false;
		return prepoint;
	}
	else return 0;
}