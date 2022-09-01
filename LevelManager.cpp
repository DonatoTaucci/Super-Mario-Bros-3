#include "LevelManager.h"
#include <iostream>
#include "Background.h"
#include "Mario.h"
#include "Sprites.h"
#include "Terrain.h"
#include "Pipe.h"
#include "Goomba.h"
#include "Secret_box.h"
#include "Koopa.h"
#include "DonutBlock.h"
#include "TigerBlock.h"
#include "Clouds.h"
#include "BlackBackgroud.h"
#include "Brick.h"
#include "Card.h"
#include "Plant.h"
#include "SecretRoomWall.h"
#include "StarBackground.h"
#include "Coin.h"
#include "Fire_chomper.h"
#include "Hit_pixmap.h"
#include <QSoundEffect>

// load all items from the given level in the given scene
Mario* LevelManager::load(std::string level_name, QGraphicsScene* scene, bool _big, bool _raccoon, bool _tanooki)
{
	Mario* mario = 0;
	new Hud(QPoint(0, 12 * 16 + 1));

	// terrain level
	int terrain_level = 11 * 16;


	if (level_name == "World-1-1-pipe")
	{
		// set background color
		scene->setBackgroundBrush(QBrush(QColor(180, 241, 241)));
		mario = new Mario(QPoint(94.5 * 16, terrain_level - 9 * 16), _big, _raccoon, _tanooki);

		mario->setPipeCounter(0);
		mario->setUpDown(true);
		mario->setPipeCheck(true);

		// terrain
		new Terrain(QRect(128 * 16, terrain_level, 33 * 16, 1 * 16));

		//coin
		new Coin(QPoint(65 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(66 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(67 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(68 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(69 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(70 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(71 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(65 * 16, terrain_level), false);
		new Coin(QPoint(66 * 16, terrain_level), false);
		new Coin(QPoint(67 * 16, terrain_level), false);
		new Coin(QPoint(68 * 16, terrain_level), false);
		new Coin(QPoint(69 * 16, terrain_level), false);
		new Coin(QPoint(70 * 16, terrain_level), false);
		new Coin(QPoint(71 * 16, terrain_level), false);

		//clouds
		new Clouds(QPoint(5 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(8 * 16, terrain_level - 10 * 16), 0);
		new Clouds(QPoint(13 * 16, terrain_level - 8 * 16), 1);
		new Clouds(QPoint(18 * 16, terrain_level - 11 * 16), 1);
		new Clouds(QPoint(20 * 16, terrain_level - 7 * 16), 0);
		new Clouds(QPoint(25 * 16, terrain_level - 8 * 16), 1);
		new Clouds(QPoint(28 * 16, terrain_level - 10 * 16), 0);
		new Clouds(QPoint(31 * 16, terrain_level - 7 * 16), 1);
		new Clouds(QPoint(36 * 16, terrain_level - 8 * 16), 1);
		new Clouds(QPoint(40 * 16, terrain_level - 7 * 16), 0);
		new Clouds(QPoint(42 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(45 * 16, terrain_level - 7 * 16), 1);
		new Clouds(QPoint(52 * 16, terrain_level - 9 * 16), 1);
		new Clouds(QPoint(58 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(61 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(63 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(65 * 16, terrain_level - 7 * 16), 1);
		new Clouds(QPoint(69 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(74 * 16, terrain_level - 8 * 16), 0);
		new Clouds(QPoint(78 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(79 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(82 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(83 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(86 * 16, terrain_level - 8 * 16), 0);
		new Clouds(QPoint(92  * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(98 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(105 * 16, terrain_level - 7 * 16), 1);
		new Clouds(QPoint(109 * 16, terrain_level - 7 * 16), 1);
		new Clouds(QPoint(112 * 16, terrain_level - 9 * 16), 0);
		new Clouds(QPoint(116 * 16, terrain_level - 8 * 16), 1);
		new Clouds(QPoint(117 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(120 * 16, terrain_level - 7 * 16), 0);
		new Clouds(QPoint(121 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(123 * 16, terrain_level - 5 * 16), 1);
		new Clouds(QPoint(127 * 16, terrain_level - 8 * 16), 1);

		// pipes
		new Pipe(QPoint(30 * 16, terrain_level + 1 * 16), 3);
		new Pipe(QPoint(36 * 16, terrain_level + 1 * 16), 3, false, true);
		new Pipe(QPoint(55 * 16, terrain_level + 1 * 16), 3);
		new Pipe(QPoint(84 * 16, terrain_level + 1 * 16), 3);
		new Pipe(QPoint(48 * 16, terrain_level - 8 * 16), 16, true);
		new Pipe(QPoint(94 * 16, terrain_level - 9 * 16), 16, true);
		new Pipe(QPoint(105 * 16, terrain_level - 9 * 16), 16, true);

		//donutblocks
		for (int i = 0; i < 27; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level), mario);
		new DonutBlock(QPoint(27 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(28 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(29 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(32 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(33 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(34 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(35 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(38 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(39 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(40 * 16, terrain_level - 2 * 16), mario);
		for (int i = 41; i < 55; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level), mario);
		for (int i = 57; i < 65; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level), mario);
		for (int i = 65; i < 72; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level - 2 * 16), mario);
		for (int i = 72; i < 81; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level), mario);
		for (int i = 89; i < 128; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level), mario);

		//bricks
		new Brick(QPoint(30 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(31 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(36 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(37 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(100 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(100 * 16, terrain_level - 5 * 16));
		new Brick(QPoint(99 * 16, terrain_level - 8 * 16), true, COIN);
		new Brick(QPoint(100 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(101 * 16, terrain_level - 8 * 16), true, LEAF);
		new Brick(QPoint(3 * 16, terrain_level - 6 * 16));
		new Brick(QPoint(7 * 16, terrain_level - 5 * 16), true, COIN);

		//tiger blocks
		new TigerBlock(QPoint(2 * 16, terrain_level - 3 * 16));
		new TigerBlock(QPoint(8 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(17 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(26 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(26 * 16, terrain_level - 2 * 16));
		new TigerBlock(QPoint(26 * 16, terrain_level - 3 * 16), true);
		new TigerBlock(QPoint(41 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(41 * 16, terrain_level - 2 * 16));
		new TigerBlock(QPoint(41 * 16, terrain_level - 3 * 16));
		new TigerBlock(QPoint(64 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(64 * 16, terrain_level - 2 * 16));
		new TigerBlock(QPoint(72 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(72 * 16, terrain_level - 2 * 16));
		new TigerBlock(QPoint(80 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(89 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(96 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(104 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(112 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(120 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(99 * 16, terrain_level - 3 * 16));
		new TigerBlock(QPoint(99 * 16, terrain_level - 4 * 16));
		new TigerBlock(QPoint(98 * 16, terrain_level - 4 * 16));
		new TigerBlock(QPoint(98 * 16, terrain_level - 5 * 16));
		new TigerBlock(QPoint(98 * 16, terrain_level - 6 * 16));
		new TigerBlock(QPoint(98 * 16, terrain_level - 7 * 16));
		new TigerBlock(QPoint(101 * 16, terrain_level - 3 * 16));
		new TigerBlock(QPoint(101 * 16, terrain_level - 4 * 16));
		new TigerBlock(QPoint(102 * 16, terrain_level - 4 * 16));
		new TigerBlock(QPoint(102 * 16, terrain_level - 5 * 16));
		new TigerBlock(QPoint(102 * 16, terrain_level - 6 * 16));
		new TigerBlock(QPoint(102 * 16, terrain_level - 7 * 16));
		for (int i = 0; i < 128; i++)
			new TigerBlock(QPoint((i) * 16, terrain_level - 25 * 16));
		new TigerBlock(QPoint(161 * 16, terrain_level));

		// secret boxes
		new SecretBox(QPoint(2 * 16, terrain_level - 6 * 16), LEAF);
		new SecretBox(QPoint(47 * 16, terrain_level - 4 * 16), LEAF);
		new SecretBox(QPoint(48 * 16, terrain_level - 4 * 16));
		new SecretBox(QPoint(49 * 16, terrain_level - 4 * 16));
		new SecretBox(QPoint(50 * 16, terrain_level - 4 * 16));

		//final background
		for (int i = 0; i < 27; i++) {
			new BlackBackground(QPoint(136 * 16, terrain_level - (i) * 16), 1);
			for (int j = 137; j < 160; j++)
				new BlackBackground(QPoint((j) * 16, terrain_level - (i) * 16), 0);
		};
		new BlackBackground(QPoint(145 * 16, terrain_level - 6 * 16), 3);
		new BlackBackground(QPoint(146 * 16, terrain_level - 6 * 16), 4);
		new BlackBackground(QPoint(147 * 16, terrain_level - 6 * 16), 4);
		new BlackBackground(QPoint(148 * 16, terrain_level - 6 * 16), 5);
		new BlackBackground(QPoint(145 * 16, terrain_level - 5 * 16), 6);
		new BlackBackground(QPoint(146 * 16, terrain_level - 5 * 16), 7);
		new BlackBackground(QPoint(147 * 16, terrain_level - 5 * 16), 7);
		new BlackBackground(QPoint(148 * 16, terrain_level - 5 * 16), 8);
		new BlackBackground(QPoint(145 * 16, terrain_level - 4 * 16), 6);
		new BlackBackground(QPoint(146 * 16, terrain_level - 4 * 16), 7);
		new BlackBackground(QPoint(147 * 16, terrain_level - 4 * 16), 7);
		new BlackBackground(QPoint(148 * 16, terrain_level - 4 * 16), 8);
		new BlackBackground(QPoint(145 * 16, terrain_level - 3 * 16), 6);
		new BlackBackground(QPoint(146 * 16, terrain_level - 3 * 16), 7);
		new BlackBackground(QPoint(147 * 16, terrain_level - 3 * 16), 7);
		new BlackBackground(QPoint(148 * 16, terrain_level - 3 * 16), 8);
		new BlackBackground(QPoint(145 * 16, terrain_level - 2 * 16), 6);
		new BlackBackground(QPoint(146 * 16, terrain_level - 2 * 16), 7);
		new BlackBackground(QPoint(147 * 16, terrain_level - 2 * 16), 3);
		new BlackBackground(QPoint(148 * 16, terrain_level - 2 * 16), 4);
		new BlackBackground(QPoint(149 * 16, terrain_level - 2 * 16), 4);
		new BlackBackground(QPoint(150 * 16, terrain_level - 2 * 16), 5);
		new BlackBackground(QPoint(145 * 16, terrain_level - 1 * 16), 6);
		new BlackBackground(QPoint(146 * 16, terrain_level - 1 * 16), 7);
		new BlackBackground(QPoint(147 * 16, terrain_level - 1 * 16), 6);
		new BlackBackground(QPoint(148 * 16, terrain_level - 1 * 16), 7);
		new BlackBackground(QPoint(149 * 16, terrain_level - 1 * 16), 7);
		new BlackBackground(QPoint(150 * 16, terrain_level - 1 * 16), 8);
		new BlackBackground(QPoint(157 * 16, terrain_level - 5 * 16), 3);
		new BlackBackground(QPoint(158 * 16, terrain_level - 5 * 16), 4);
		new BlackBackground(QPoint(159 * 16, terrain_level - 5 * 16), 5);
		new BlackBackground(QPoint(157 * 16, terrain_level - 4 * 16), 6);
		new BlackBackground(QPoint(158 * 16, terrain_level - 4 * 16), 7);
		new BlackBackground(QPoint(159 * 16, terrain_level - 4 * 16), 8);
		new BlackBackground(QPoint(155 * 16, terrain_level - 3 * 16), 3);
		new BlackBackground(QPoint(156 * 16, terrain_level - 3 * 16), 4);
		new BlackBackground(QPoint(157 * 16, terrain_level - 3 * 16), 5);
		new BlackBackground(QPoint(158 * 16, terrain_level - 3 * 16), 7);
		new BlackBackground(QPoint(159 * 16, terrain_level - 3 * 16), 8);
		new BlackBackground(QPoint(155 * 16, terrain_level - 2 * 16), 6);
		new BlackBackground(QPoint(156 * 16, terrain_level - 2 * 16), 7);
		new BlackBackground(QPoint(157 * 16, terrain_level - 2 * 16), 8);
		new BlackBackground(QPoint(158 * 16, terrain_level - 2 * 16), 7);
		new BlackBackground(QPoint(159 * 16, terrain_level - 2 * 16), 8);
		new BlackBackground(QPoint(155 * 16, terrain_level - 1 * 16), 6);
		new BlackBackground(QPoint(156 * 16, terrain_level - 1 * 16), 7);
		new BlackBackground(QPoint(157 * 16, terrain_level - 1 * 16), 8);
		new BlackBackground(QPoint(158 * 16, terrain_level - 1 * 16), 7);
		new BlackBackground(QPoint(159 * 16, terrain_level - 1 * 16), 8);
		new BlackBackground(QPoint(151.7 * 16, terrain_level - 5.3 * 16), 9);

		//roulette
		new Card(QPoint(152 * 16, terrain_level - 4 * 16));

		// enemies
		new Koopa(QPoint(18 * 16, terrain_level - 3 * 16), true);
		new Koopa(QPoint(112 * 16, terrain_level - 3 * 16), true);
		new Koopa(QPoint(24 * 16, terrain_level - 2 * 16), true);
		new Koopa(QPoint(45 * 16, terrain_level - 2 * 16), true);
		new Goomba(QPoint(20 * 16, terrain_level - 2 * 16), true);
		new Goomba(QPoint(78 * 16, terrain_level - 2 * 16), true);
		new Goomba(QPoint(120 * 16, terrain_level - 2 * 16), true);
		new Fire_chomper(QPoint(82 * 16, terrain_level - 7 * 16));		
		new Plant(QPoint(84.5 * 16, terrain_level - 0.8 * 16), LEFT, false, false);
		new Plant(QPoint(55.5 * 16, terrain_level - 0.8 * 16));
		new Plant(QPoint(48.5 * 16, terrain_level - 6.1 * 16), LEFT, true);
		new Plant(QPoint(105.5 * 16, terrain_level - 7.1 * 16), LEFT, true);
	}
	
	else if (level_name == "World-1-1")
		{
		// set background color
		scene->setBackgroundBrush(QBrush(QColor(180, 241, 241)));
		mario = new Mario(QPoint(2 * 16, terrain_level - 4 * 16));

		// terrain
		new Terrain(QRect(128 * 16, terrain_level, 33 * 16, 1 * 16));

		//coin
		new Coin(QPoint(65 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(66 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(67 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(68 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(69 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(70 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(71 * 16, terrain_level - 4 * 16), false);
		new Coin(QPoint(65 * 16, terrain_level), false);
		new Coin(QPoint(66 * 16, terrain_level), false);
		new Coin(QPoint(67 * 16, terrain_level), false);
		new Coin(QPoint(68 * 16, terrain_level), false);
		new Coin(QPoint(69 * 16, terrain_level), false);
		new Coin(QPoint(70 * 16, terrain_level), false);
		new Coin(QPoint(71 * 16, terrain_level), false);

		//clouds
		new Clouds(QPoint(5 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(8 * 16, terrain_level - 10 * 16), 0);
		new Clouds(QPoint(13 * 16, terrain_level - 8 * 16), 1);
		new Clouds(QPoint(18 * 16, terrain_level - 11 * 16), 1);
		new Clouds(QPoint(20 * 16, terrain_level - 7 * 16), 0);
		new Clouds(QPoint(25 * 16, terrain_level - 8 * 16), 1);
		new Clouds(QPoint(28 * 16, terrain_level - 10 * 16), 0);
		new Clouds(QPoint(31 * 16, terrain_level - 7 * 16), 1);
		new Clouds(QPoint(36 * 16, terrain_level - 8 * 16), 1);
		new Clouds(QPoint(40 * 16, terrain_level - 7 * 16), 0);
		new Clouds(QPoint(42 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(45 * 16, terrain_level - 7 * 16), 1);
		new Clouds(QPoint(52 * 16, terrain_level - 9 * 16), 1);
		new Clouds(QPoint(58 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(61 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(63 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(65 * 16, terrain_level - 7 * 16), 1);
		new Clouds(QPoint(69 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(74 * 16, terrain_level - 8 * 16), 0);
		new Clouds(QPoint(78 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(79 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(82 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(83 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(86 * 16, terrain_level - 8 * 16), 0);
		new Clouds(QPoint(92 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(98 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(105 * 16, terrain_level - 7 * 16), 1);
		new Clouds(QPoint(109 * 16, terrain_level - 7 * 16), 1);
		new Clouds(QPoint(112 * 16, terrain_level - 9 * 16), 0);
		new Clouds(QPoint(116 * 16, terrain_level - 8 * 16), 1);
		new Clouds(QPoint(117 * 16, terrain_level - 6 * 16), 1);
		new Clouds(QPoint(120 * 16, terrain_level - 7 * 16), 0);
		new Clouds(QPoint(121 * 16, terrain_level - 10 * 16), 1);
		new Clouds(QPoint(123 * 16, terrain_level - 5 * 16), 1);
		new Clouds(QPoint(127 * 16, terrain_level - 8 * 16), 1);

		// pipes
		new Pipe(QPoint(30 * 16, terrain_level + 1 * 16), 3);
		new Pipe(QPoint(36 * 16, terrain_level + 1 * 16), 3, false, true);
		new Pipe(QPoint(55 * 16, terrain_level + 1 * 16), 3);
		new Pipe(QPoint(84 * 16, terrain_level + 1 * 16), 3);
		new Pipe(QPoint(48 * 16, terrain_level - 8 * 16), 16, true);
		new Pipe(QPoint(94 * 16, terrain_level - 9 * 16), 16, true);
		new Pipe(QPoint(105 * 16, terrain_level - 9 * 16), 16, true);

		//donutblocks
		new DonutBlock(QPoint(27 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(28 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(29 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(32 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(33 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(34 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(35 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(38 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(39 * 16, terrain_level - 2 * 16), mario);
		new DonutBlock(QPoint(40 * 16, terrain_level - 2 * 16), mario);
		for (int i = 0; i < 27; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level), mario);
		for (int i = 41; i < 55; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level), mario);
		for (int i = 57; i < 65; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level), mario);
		for (int i = 65; i < 72; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level - 2 * 16), mario);
		for (int i = 72; i < 81; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level), mario);
		for (int i = 89; i < 128; i++)
			new DonutBlock(QPoint((i) * 16, terrain_level), mario);

		//tiger blocks
		new TigerBlock(QPoint(2 * 16, terrain_level - 3 * 16));
		new TigerBlock(QPoint(8 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(9 * 16, terrain_level - 4 * 16));
		new TigerBlock(QPoint(17 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(26 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(26 * 16, terrain_level - 2 * 16));
		new TigerBlock(QPoint(26 * 16, terrain_level - 3 * 16), true);
		new TigerBlock(QPoint(41 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(41 * 16, terrain_level - 2 * 16));
		new TigerBlock(QPoint(41 * 16, terrain_level - 3 * 16));
		new TigerBlock(QPoint(64 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(64 * 16, terrain_level - 2 * 16));
		new TigerBlock(QPoint(72 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(72 * 16, terrain_level - 2 * 16));
		new TigerBlock(QPoint(80 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(89 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(96 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(104 * 16, terrain_level - 1 * 16), true);
		new TigerBlock(QPoint(112 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(120 * 16, terrain_level - 1 * 16));
		new TigerBlock(QPoint(99 * 16, terrain_level - 3 * 16));
		new TigerBlock(QPoint(99 * 16, terrain_level - 4 * 16));
		new TigerBlock(QPoint(98 * 16, terrain_level - 4 * 16));
		new TigerBlock(QPoint(98 * 16, terrain_level - 5 * 16));
		new TigerBlock(QPoint(98 * 16, terrain_level - 6 * 16));
		new TigerBlock(QPoint(98 * 16, terrain_level - 7 * 16));
		new TigerBlock(QPoint(101 * 16, terrain_level - 3 * 16));
		new TigerBlock(QPoint(101 * 16, terrain_level - 4 * 16));
		new TigerBlock(QPoint(102 * 16, terrain_level - 4 * 16));
		new TigerBlock(QPoint(102 * 16, terrain_level - 5 * 16));
		new TigerBlock(QPoint(102 * 16, terrain_level - 6 * 16));
		new TigerBlock(QPoint(102 * 16, terrain_level - 7 * 16));
		for (int i = 0; i < 128; i++)
			new TigerBlock(QPoint((i) * 16, terrain_level - 25 * 16));
		new TigerBlock(QPoint(161 * 16, terrain_level));

		// secret boxes
		new SecretBox(QPoint(47 * 16, terrain_level - 4 * 16), LEAF);
		new SecretBox(QPoint(48 * 16, terrain_level - 4 * 16));
		new SecretBox(QPoint(49 * 16, terrain_level - 4 * 16));
		new SecretBox(QPoint(50 * 16, terrain_level - 4 * 16));

		//bricks
		new Brick(QPoint(30 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(31 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(36 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(37 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(100 * 16, terrain_level - 4 * 16));
		new Brick(QPoint(100 * 16, terrain_level - 5 * 16));
		new Brick(QPoint(99 * 16, terrain_level - 8 * 16), true, COIN);
		new Brick(QPoint(100 * 16, terrain_level - 8 * 16));
		new Brick(QPoint(101 * 16, terrain_level - 8 * 16), true, LEAF);

		//final background
		for (int i = 0; i < 27; i++) {
			new BlackBackground(QPoint(136 * 16, terrain_level - (i) * 16), 1);
			for (int j = 137; j < 160; j++)
				new BlackBackground(QPoint((j) * 16, terrain_level - (i) * 16), 0);
		};
		new BlackBackground(QPoint(145 * 16, terrain_level - 6 * 16), 3);
		new BlackBackground(QPoint(146 * 16, terrain_level - 6 * 16), 4);
		new BlackBackground(QPoint(147 * 16, terrain_level - 6 * 16), 4);
		new BlackBackground(QPoint(148 * 16, terrain_level - 6 * 16), 5);
		new BlackBackground(QPoint(145 * 16, terrain_level - 5 * 16), 6);
		new BlackBackground(QPoint(146 * 16, terrain_level - 5 * 16), 7);
		new BlackBackground(QPoint(147 * 16, terrain_level - 5 * 16), 7);
		new BlackBackground(QPoint(148 * 16, terrain_level - 5 * 16), 8);
		new BlackBackground(QPoint(145 * 16, terrain_level - 4 * 16), 6);
		new BlackBackground(QPoint(146 * 16, terrain_level - 4 * 16), 7);
		new BlackBackground(QPoint(147 * 16, terrain_level - 4 * 16), 7);
		new BlackBackground(QPoint(148 * 16, terrain_level - 4 * 16), 8);
		new BlackBackground(QPoint(145 * 16, terrain_level - 3 * 16), 6);
		new BlackBackground(QPoint(146 * 16, terrain_level - 3 * 16), 7);
		new BlackBackground(QPoint(147 * 16, terrain_level - 3 * 16), 7);
		new BlackBackground(QPoint(148 * 16, terrain_level - 3 * 16), 8);
		new BlackBackground(QPoint(145 * 16, terrain_level - 2 * 16), 6);
		new BlackBackground(QPoint(146 * 16, terrain_level - 2 * 16), 7);
		new BlackBackground(QPoint(147 * 16, terrain_level - 2 * 16), 3);
		new BlackBackground(QPoint(148 * 16, terrain_level - 2 * 16), 4);
		new BlackBackground(QPoint(149 * 16, terrain_level - 2 * 16), 4);
		new BlackBackground(QPoint(150 * 16, terrain_level - 2 * 16), 5);
		new BlackBackground(QPoint(145 * 16, terrain_level - 1 * 16), 6);
		new BlackBackground(QPoint(146 * 16, terrain_level - 1 * 16), 7);
		new BlackBackground(QPoint(147 * 16, terrain_level - 1 * 16), 6);
		new BlackBackground(QPoint(148 * 16, terrain_level - 1 * 16), 7);
		new BlackBackground(QPoint(149 * 16, terrain_level - 1 * 16), 7);
		new BlackBackground(QPoint(150 * 16, terrain_level - 1 * 16), 8);
		new BlackBackground(QPoint(157 * 16, terrain_level - 5 * 16), 3);
		new BlackBackground(QPoint(158 * 16, terrain_level - 5 * 16), 4);
		new BlackBackground(QPoint(159 * 16, terrain_level - 5 * 16), 5);
		new BlackBackground(QPoint(157 * 16, terrain_level - 4 * 16), 6);
		new BlackBackground(QPoint(158 * 16, terrain_level - 4 * 16), 7);
		new BlackBackground(QPoint(159 * 16, terrain_level - 4 * 16), 8);
		new BlackBackground(QPoint(155 * 16, terrain_level - 3 * 16), 3);
		new BlackBackground(QPoint(156 * 16, terrain_level - 3 * 16), 4);
		new BlackBackground(QPoint(157 * 16, terrain_level - 3 * 16), 5);
		new BlackBackground(QPoint(158 * 16, terrain_level - 3 * 16), 7);
		new BlackBackground(QPoint(159 * 16, terrain_level - 3 * 16), 8);
		new BlackBackground(QPoint(155 * 16, terrain_level - 2 * 16), 6);
		new BlackBackground(QPoint(156 * 16, terrain_level - 2 * 16), 7);
		new BlackBackground(QPoint(157 * 16, terrain_level - 2 * 16), 8);
		new BlackBackground(QPoint(158 * 16, terrain_level - 2 * 16), 7);
		new BlackBackground(QPoint(159 * 16, terrain_level - 2 * 16), 8);
		new BlackBackground(QPoint(155 * 16, terrain_level - 1 * 16), 6);
		new BlackBackground(QPoint(156 * 16, terrain_level - 1 * 16), 7);
		new BlackBackground(QPoint(157 * 16, terrain_level - 1 * 16), 8);
		new BlackBackground(QPoint(158 * 16, terrain_level - 1 * 16), 7);
		new BlackBackground(QPoint(159 * 16, terrain_level - 1 * 16), 8);
		new BlackBackground(QPoint(151.7 * 16, terrain_level - 5.3 * 16), 9);

		//roulette
		new Card(QPoint(152 * 16, terrain_level - 4 * 16));

		// enemies
		new Koopa(QPoint(18 * 16, terrain_level - 3 * 16), true);
		new Koopa(QPoint(24 * 16, terrain_level - 2 * 16), true);
		new Koopa(QPoint(45 * 16, terrain_level - 2 * 16), true);
		new Koopa(QPoint(112 * 16, terrain_level - 3 * 16), true);
		new Goomba(QPoint(20 * 16, terrain_level - 2 * 16), true);
		new Goomba(QPoint(78 * 16, terrain_level - 2 * 16), true);
		new Goomba(QPoint(120 * 16, terrain_level - 2 * 16),true);
		new Fire_chomper(QPoint(85 * 16, terrain_level - 7 * 16));
		new Plant(QPoint(48.5 * 16, terrain_level - 6.1 * 16), LEFT, true, true);
		new Plant(QPoint(55.5 * 16, terrain_level - 0.8 * 16));
		new Plant(QPoint(84.5 * 16, terrain_level - 0.8 * 16), LEFT, false, false);		
		new Plant(QPoint(105.5 * 16, terrain_level - 7.1 * 16), LEFT, true);
	}
	else if (level_name == "Secret-room")
	{
		scene->clear();
		mario = new Mario(QPoint(1.5 * 16, terrain_level - 22 * 16), _big, _raccoon, _tanooki);

		mario->setPipeCounter(0);
		mario->setUpDown(true);
		mario->setPipeCheck(true);

		scene->setBackgroundBrush(QBrush(QColor(0, 0, 0)));

		//secret wall
		for (int i = 25; i > 0; i--)
			new SecretRoomWall(QPoint(0 * 16, terrain_level - i * +16));
		for (int i = 0; i < 16; i++)
		{
			new SecretRoomWall(QPoint(i * 16, terrain_level));
			new SecretRoomWall(QPoint(i * 16, terrain_level + 1 * 16));
		}
		for (int i = 9; i > 0; i--)
			new SecretRoomWall(QPoint(15 * 16, terrain_level - i * 16));
		for (int i = 0; i < 13; i++)
		{
			new SecretRoomWall(QPoint((15 - i) * 16, terrain_level - 9 * 16));
			new SecretRoomWall(QPoint((15 - i) * 16, terrain_level - 10 * 16));
		}
		for (int i = 11; i < 26; i++) 
		{
			new SecretRoomWall(QPoint(3 * 16, terrain_level - i * 16));
		}
	    for (int i = 26; i > 0; i--)
		{
			new StarBackground(QPoint(1 * 16, terrain_level - i * 16));
			new StarBackground(QPoint(2 * 16, terrain_level - i * 16));
		}
		for(int j = 0 ; j < 12; j ++)
			for (int i = 1; i < 10; i++)
				new StarBackground(QPoint((3 + j) * 16, terrain_level - i * 16));

		//coin
		for (int i = 0; i < 10; i++)
		{
			if (i % 2 == 0)
				new Coin(QPoint(2 * 16, terrain_level - (20 - i) * 16), false);
			else
				new Coin(QPoint(1 * 16, terrain_level - (20 - i) * 16), false);
		}

		//pipe
		new Pipe(QPoint(1 * 16, terrain_level - 23 * 16), 2, true, false, true);
		new Pipe(QPoint(13 * 16, terrain_level - 4 * 16), 4, true, true, true);

		//secretbox
		new SecretBox(QPoint(7 * 16, terrain_level - 4 * 16), TANOOKI, true);
	}
	else
		std::cerr << "Level not implemented";

	return mario;
}
