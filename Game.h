#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsLineItem>
#include <QTimer>
#include <QSound>
#include"Goomba.h"
#include "Hud.h"
#include "Mario.h"
#include "LevelManager.h"

class Game : public QGraphicsView
{
	Q_OBJECT

		enum game_state { READY, RUNNING, PAUSE, GAME_OVER };

private:

	static Game* uniqueInstance;				// Singleton design pattern
	Game(QGraphicsView* parent = 0);			// Singleton design pattern

	QGraphicsScene* scene;						// the scene used to render the game (2D)
	Hud* hud;									// hud object
	Mario* mario;								// mario object

	QTimer engine;								// game engine / timer
	game_state cur_state;						// current game state
	QSound* music;								// game music
	QSound* max_speed;
	std::vector <QGraphicsLineItem*> grid;		// scene grid (for debugging)

	bool moveRight;								//move mario when the key is pressed
	bool moveLeft;
	bool secret_room;							//leave the world and enter the secret room
	bool back2world;							//leave the secret room and enter the world
	bool finish;
	bool first_run;								//first time the game is lanuched OR first game after mario ended all hs life
	bool other_run;								//all the other runs
	bool got_a_coin;							//true when a coin is taken
	bool got_points;							//true when points are gained

	int finish_counter;

	int coin_number;
	int point;
	int prepoint;								//points's value before new points were added
	int coinI;									//value of coin's units
	int coinJ;									//value of coin's tens
	int card;

	int lifeI;									//value of life's units
	int lifeJ;									//value of life's tens

	int pointIndex[7];

	int time1;									//value of time's units
	int time2;									//value of time's tens
	int time3;									//value of time's hundreds
	int time_left;
	int countdown;								//subtract one to time_left every 60 frames
	int max_speed_counter;

	bool marioBig;
	bool marioRaccoon;
	bool marioTanooki;

protected:

	// the game is controlled using the keyboard
	// hence we have to intercept all keyboard events
	virtual void keyPressEvent(QKeyEvent* e);
	virtual void keyReleaseEvent(QKeyEvent* e);

	// zoom-in/out (for debug)
	virtual void wheelEvent(QWheelEvent* e);

public:

	// singleton unique instance getter
	static Game* instance();

	// getters
	QGraphicsScene* getScene() { return scene; }

	void changeScene();


public slots:

	// advance game / next frame
	void advance();

	// pause / resume game
	void tooglePause();

	// show/ hide level grid
	void toogleGrid();

	// show/ hide object colliders
	void toogleColliders();

	// reset game
	void reset();

	// start new game
	void start();

	// game over
	void gameover();

	// stop music
	void stopMusic();


	//setters
	void setFreezed(bool freezed);												// freeze/unfreeze all entities
	void setGotCoin(bool _got_a_coin) { got_a_coin = _got_a_coin; }				//function called in Hud.cpp
	void setGotPoints(bool _in_point) { got_points = _in_point; }				//function called in Hud.cpp
	void setHud(Hud* _hud) { hud = _hud; }
	void setFinish(bool _finish) { finish = _finish; }
	void setCard(int _card) { card = _card; }

	//getters
	Mario* getMario() { return mario; }											//return mario
	bool getGotCoin() { return got_a_coin; }									//function called in Hud.cpp
	int getGotPoints();															//function called in Hud.cpp
	int getTime1() { return time1; }											//function called in Hud.cpp
	int getTime2() { return time2; }											//function called in Hud.cpp
	int getTime3() { return time3; }											//function called in Hud.cpp
	bool getFinish() { return finish; }

	//other functions
	void sumCoin(int coin) { coin_number = coin_number + coin; got_a_coin = true; }
	void sumPoint(int _point) { prepoint = point; point = point + _point; prepoint = point - prepoint; got_points = true; }
	void losingLife() { lifeI--;}
};
