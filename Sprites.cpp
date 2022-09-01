#include "Sprites.h"
#include "utils.h"
#include <QBitmap>

// utility function
QRect moveBy(QRect rect, int x, int y, int dx = 16, int dy = 16, int border_x = 1, int border_y = 1)
{
	rect.moveTo(QPoint(rect.x() + x * dx + x * border_x, rect.y() + y * dy + y * border_y));
	return rect;
}

QRect moveRight(QRect rect, int pixels)
{
	rect.translate(QPoint(pixels, 0));
	return rect;
}


QRect moveMarioBy(QRect rect, int x, int y, int dx = 16, int dy = 16)
{
	return moveBy(rect, x, y, dx, dy, 2, 2);
}

// main object positions within sprites
static QRect mario_small(1, 16, 16, 16);
static QRect mario_big(1, 93, 16, 27);
static QRect terrain(443, 154, 16, 16);
static QRect hud_panel(3, 3, 232, 28);
static QRect pipe(69, 35, 16, 16);
static QRect goomba_brown(0, 0, 16, 15);
static QRect goomba_red(88, 0, 16, 15);
static QRect secret_box(1140, 1, 16, 16);
static QRect box_coin(290, 101, 16, 14);
static QRect koopa(0, 51, 16, 25);
static QRect cloud(192, 0, 17, 17);
static QRect brick(1038, 1, 16, 16);
static QRect brick_debris(1089, 103, 8, 9);


Sprites* Sprites::instance()
{
	static Sprites uniqueInstance;
	return &uniqueInstance;
}

Sprites::Sprites()
{
	hud = loadTexture(":/graphics/sprites/hud.png", Qt::magenta);
	mario = loadTexture(":/graphics/sprites/mario.png", QColor(68, 145, 190));
	enemies = loadTexture(":/graphics/sprites/enemies.png", QColor(68, 145, 190));
	stage_tiles = loadTexture(":/graphics/sprites/stage_tiles.png", QColor(224, 163, 216));
	title_screen = loadTexture(":/graphics/sprites/title_screen.png");
	miscs = loadTexture(":/graphics/sprites/miscs.png", QColor(166, 185, 255));
	winged_enemies = loadTexture(":/graphics/sprites/winged_enemies.png", QColor(68, 145, 190));
	card = loadTexture(":/graphics/sprites/goal_roulette.png", QColor(0, 183, 239));
	point = loadTexture(":/graphics/sprites/misc-6.png", QColor(255, 150, 255));
}

QPixmap Sprites::get(const std::string& id)
{
	if (id == "mario-small-stand")
		return mario.copy(mario_small);
	else if (id == "mario-small-walk-0")
		return mario.copy(mario_small);
	else if (id == "mario-small-walk-1")
		return mario.copy(moveMarioBy(mario_small, 1, 0));
	else if (id == "mario-small-walk-2")
		return mario.copy(mario_small);
	else if (id == "mario-small-walk-3")
		return mario.copy(moveMarioBy(mario_small, 1, 0));
	else if (id == "mario-small-fall")
		return mario.copy(moveMarioBy(mario_small, 2, 0));
	else if (id == "mario-small-jump")
		return mario.copy(moveMarioBy(mario_small, 2, 0));
	else if (id == "mario-small-run-0")
		return mario.copy(moveMarioBy(mario_small, 3, 0));
	else if (id == "mario-small-run-1")
		return mario.copy(moveMarioBy(mario_small, 4, 0));
	else if (id == "mario-small-run-2")
		return mario.copy(moveMarioBy(mario_small, 3, 0));
	else if (id == "mario-small-run-3")
		return mario.copy(moveMarioBy(mario_small, 4, 0));
	else if (id == "mario-small-jump-run")
		return mario.copy(moveMarioBy(mario_small, 5, 0));
	else if (id == "mario-small-fall-run")
		return mario.copy(moveMarioBy(mario_small, 5, 0));
	else if (id == "mario-small-brake")
		return mario.copy(moveMarioBy(mario_small, 6, 0));
	else if (id == "mario-small-inv")
		return hud.copy(QRect(233, 108, 16, 16));
	else if (id == "mario-small-kick")
		return mario.copy(moveMarioBy(mario_small, 10, 0));
	else if (id == "mario-pipe-small")
		return mario.copy(QRect(127, 16, 16, 16));

	else if (id == "mario-half-transf")
		return mario.copy(QRect(209, 132, 15, 22));

	else if (id == "mario-big-stand")
		return mario.copy(QRect(1, 91, 16, 29));
	else if (id == "mario-big-walk-0")
		return mario.copy(QRect(1, 91, 16, 29));
	else if (id == "mario-big-walk-1")
		return mario.copy(QRect(19, 91, 16, 29));
	else if (id == "mario-big-walk-2")
		return mario.copy(QRect(37, 90, 16, 29));
	else if (id == "mario-big-walk-3")
		return mario.copy(QRect(19, 91, 16, 29));
	else if (id == "mario-big-fall")
		return mario.copy(QRect(37, 90, 16, 29));
	else if (id == "mario-big-jump")
		return mario.copy(QRect(73, 90, 16, 29));
	else if (id == "mario-big-run-0")
		return mario.copy(QRect(117, 91, 19, 29));
	else if (id == "mario-big-run-1")
		return mario.copy(QRect(91, 91, 19, 29));
	else if (id == "mario-big-run-2")
		return mario.copy(QRect(143, 91, 19, 29));
	else if (id == "mario-big-run-3")
		return mario.copy(QRect(91, 91, 19, 29));
	else if (id == "mario-big-brake")
		return mario.copy(QRect(195, 91, 16, 29));
	else if (id == "mario-big-jump-run")
		return mario.copy(QRect(169, 90, 19, 29));
	else if (id == "mario-big-fall-run")
		return mario.copy(QRect(169, 90, 19, 29));
	else if (id == "mario-big-crouch")
		return mario.copy(QRect(55, 102, 16, 18));
	else if (id == "mario-big-inv")
		return hud.copy(QRect(233, 108, 16, 16));
	else if (id == "mario-big-kick")
		return mario.copy(QRect(306, 91, 20, 29));
	else if (id == "mario-pipe-big")
		return mario.copy(QRect(213, 93, 16, 27));

	else if (id == "mario-raccoon-stand")
		return mario.copy(QRect(1, 349, 23, 29));
	else if (id == "mario-raccoon-walk-0")
		return mario.copy(QRect(1, 349, 23, 29));
	else if (id == "mario-raccoon-walk-1")
		return mario.copy(QRect(28, 349, 23, 29));
	else if (id == "mario-raccoon-walk-2")
		return mario.copy(QRect(53, 349, 23, 29));
	else if (id == "mario-raccoon-walk-3")
		return mario.copy(QRect(28, 349, 23, 29));
	else if (id == "mario-raccoon-jump")
		return mario.copy(QRect(105, 349, 23, 29));
	else if (id == "mario-raccoon-fall")
		return mario.copy(QRect(131, 349, 23, 29));
	else if (id == "mario-raccoon-brake")
		return mario.copy(QRect(339, 349, 16, 29));
	else if (id == "mario-raccoon-crouch")
		return mario.copy(QRect(79, 360, 22, 18));
	else if (id == "mario-raccoon-spin-0")
		return mario.copy(QRect(357, 349, 16, 29));
	else if (id == "mario-raccoon-spin-1")
		return mario.copy(QRect(375, 349, 23, 29));
	else if (id == "mario-raccoon-spin-2")
		return mario.copy(QRect(401, 349, 16, 29));
	else if (id == "mario-raccoon-run-0")
		return mario.copy(QRect(183, 349, 24, 29));
	else if (id == "mario-raccoon-run-1")
		return mario.copy(QRect(209, 349, 24, 29));
	else if (id == "mario-raccoon-run-2")
		return mario.copy(QRect(235, 348, 24, 29));
	else if (id == "mario-raccoon-jump-run")
		return mario.copy(QRect(261, 349, 24, 29));
	else if (id == "mario-raccoon-fall-run")
		return mario.copy(QRect(313, 348, 24, 29));
	else if (id == "mario-raccoon-gliding-0")
		return mario.copy(QRect(131, 348, 23, 29));
	else if (id == "mario-raccoon-gliding-1")
		return mario.copy(QRect(157, 349, 22, 29));
	else if (id == "mario-raccoon-flying")
		return mario.copy(QRect(287, 348, 24, 29));
	else if (id == "mario-raccoon-kick")
		return mario.copy(QRect(81, 383, 22, 29));
	else if (id == "mario-pipe-raccoon")
		return mario.copy(QRect(357, 350, 16, 28));

	if (id == "mario-tanooki-stand")
		return mario.copy(QRect(1, 573, 21, 29));
	else if (id == "mario-tanooki-walk-0")
		return mario.copy(QRect(1, 573, 21, 29));
	else if (id == "mario-tanooki-walk-1")
		return mario.copy(QRect(27, 573, 22, 29));
	else if (id == "mario-tanooki-walk-2")
		return mario.copy(QRect(53, 574, 23, 27));
	else if (id == "mario-tanooki-walk-3")
		return mario.copy(QRect(27, 573, 23, 29));
	else if (id == "mario-tanooki-run-0")
		return mario.copy(QRect(183, 573, 23, 29));
	else if (id == "mario-tanooki-run-1")
		return mario.copy(QRect(209, 573, 23, 29));
	else if (id == "mario-tanooki-run-2")
		return mario.copy(QRect(235, 572, 23, 29));
	else if (id == "mario-tanooki-jump")
		return mario.copy(QRect(105, 572, 23, 29));
	else if (id == "mario-tanooki-fall")
		return mario.copy(QRect(131, 572, 23, 29));
	else if (id == "mario-tanooki-brake")
		return mario.copy(QRect(339, 573, 16, 29));
	else if (id == "mario-tanooki-crouch")
		return mario.copy(QRect(80, 584, 21, 18));
	else if (id == "mario-tanooki-spin-0")
		return mario.copy(QRect(357, 573, 16, 29));
	else if (id == "mario-tanooki-spin-1")
		return mario.copy(QRect(375, 573, 23, 29));
	else if (id == "mario-tanooki-spin-2")
		return mario.copy(QRect(401, 573, 16, 29));
	else if (id == "mario-tanooki-gliding-0")
		return mario.copy(QRect(131, 572, 23, 29));
	else if (id == "mario-tanooki-gliding-1")
		return mario.copy(QRect(157, 573, 22, 29));
	else if (id == "mario-tanooki-jump-run")
		return mario.copy(QRect(261, 573, 24, 29));
	else if (id == "mario-tanooki-fall-run")
		return mario.copy(QRect(313, 572, 24, 29));
	else if (id == "mario-tanooki-statue")
		return mario.copy(QRect(419, 573, 16, 29));
	else if (id == "mario-tanooki-statue-void")
		return mario.copy(QRect(484, 657, 16, 29));
	else if (id == "mario-tanooki-kick")
		return mario.copy(QRect(82, 607, 21, 29));
	else if (id == "mario-tanooki-flying")
		return mario.copy(QRect(287, 572, 24, 29));
	else if (id == "mario-pipe-tanooki")
		return mario.copy(QRect(357, 573, 16, 29));

	else if (id == "mario-small-pick-koopa-0")
		return mario.copy(QRect(145, 16, 16, 16));
	else if (id == "mario-small-pick-koopa-1")
		return mario.copy(QRect(163, 16, 16, 16));

	else if (id == "mario-big-pick-koopa-0")
		return mario.copy(QRect(249, 91, 16, 29));
	else if (id == "mario-big-pick-koopa-1")
		return mario.copy(QRect(267, 91, 16, 29));
	else if (id == "mario-big-pick-koopa-2")
		return mario.copy(QRect(285, 90, 16, 29));

	else if (id == "mario-raccoon-pick-koopa-0")
		return mario.copy(QRect(1, 383, 21, 29));
	else if (id == "mario-raccoon-pick-koopa-1")
		return mario.copy(QRect(27, 383, 22, 29));
	else if (id == "mario-raccoon-pick-koopa-2")
		return mario.copy(QRect(53, 382, 23, 29));

	else if (id == "mario-tanooki-pick-koopa-0")
		return mario.copy(QRect(1, 607, 21, 29));
	else if (id == "mario-tanooki-pick-koopa-1")
		return mario.copy(QRect(27, 607, 22, 29));
	else if (id == "mario-tanooki-pick-koopa-2")
		return mario.copy(QRect(53, 606, 23, 29));

	else if (id == "mario-death")
		return mario.copy(QRect(307, 16, 16, 16));

	else if (id == "transf-cloud-0")
		return enemies.copy(cloud);
	else if (id == "transf-cloud-1")
		return enemies.copy(moveBy(cloud, 1, 0));
	else if (id == "transf-cloud-2")
		return enemies.copy(moveBy(cloud, 2, 0));
	else if (id == "transf-cloud-3")
		return enemies.copy(moveBy(cloud, 3, 0));

	else if (id == "goomba-brown-walk-0")
		return enemies.copy(goomba_brown);
	else if (id == "goomba-brown-walk-1")
		return enemies.copy(moveBy(goomba_brown, 1, 0, 16, 16, 0));
	else if (id == "goomba-brown-smashed")
		return enemies.copy(QRect(32, 7, 16, 9));
	else if (id == "goomba-red-walk-0")
		return enemies.copy(goomba_red);
	else if (id == "goomba-red-walk-1")
		return enemies.copy(moveBy(goomba_red, 1, 0, 16, 16, 0));
	else if (id == "goomba-red-smashed")
		return enemies.copy(QRect(120, 7, 16, 9));
	else if (id == "goomba-walk-0")
		return enemies.copy(goomba_brown);
	else if (id == "goomba-walk-1")
		return enemies.copy(moveBy(goomba_brown, 1, 0, 16, 16, 0));
	else if (id == "goomba-smashed")
		return enemies.copy(QRect(32, 7, 16, 9));

	else if (id == "koopa-walk-0")
		return enemies.copy(koopa);
	else if (id == "koopa-walk-1")
		return enemies.copy(moveBy(koopa, 1, 0, 16, 26, 0));
	else if (id == "koopa-smashed")
		return enemies.copy(QRect(32, 48, 15, 15));
	else if (id == "koopa-awaking-0")
		return enemies.copy(QRect(32, 64, 16, 16));
	else if (id == "koopa-awaking-1")
		return enemies.copy(QRect(32, 48, 15, 15));
	else if (id == "koopa-roll-0")
		return enemies.copy(QRect(48, 48, 16, 16));
	else if (id == "koopa-roll-1")
		return enemies.copy(QRect(64, 48, 16, 16));
	else if (id == "koopa-roll-2")
		return enemies.copy(QRect(80, 48, 16, 16));

	else if (id == "wing-0")
		return enemies.copy(QRect(136, 2, 8, 13));
	else if (id == "wing-1")
		return enemies.copy(QRect(144, 2, 8, 14));

	else if (id == "fire-chomper-shooting-0")
		return enemies.copy(QRect(208, 512, 16, 16));
	else if (id == "fire-chomper-shooting-1")
		return enemies.copy(QRect(192, 512, 16, 16));
	else if (id == "fire-chomper-moving")
		return enemies.copy(QRect(224, 513, 16, 14));
	else if (id == "fire-chomper-explode")
		return enemies.copy(QRect(240, 561, 16, 14));

	else if (id == "green-star")
		return enemies.copy(QRect(192, 480, 16, 16));
	else if (id == "yellow-star")
		return enemies.copy(QRect(208, 480, 16, 16));
	else if (id == "black-star")
		return enemies.copy(QRect(224, 480, 16, 16));
	else if (id == "red-star")
		return enemies.copy(QRect(240, 480, 16, 16));

	else if (id == "secret-box-0")
		return stage_tiles.copy(secret_box);
	else if (id == "secret-box-1")
		return stage_tiles.copy(moveBy(secret_box, 1, 0));
	else if (id == "secret-box-2")
		return stage_tiles.copy(moveBy(secret_box, 2, 0));
	else if (id == "secret-box-3")
		return stage_tiles.copy(moveBy(secret_box, 3, 0));
	else if (id == "secret-box-inactive")
		return stage_tiles.copy(moveBy(secret_box, 4, 0));
	else if (id == "secret-box-big-active")
		return miscs.copy(QRect(194, 209, 32, 32));
	else if (id == "secret-box-big-inactive")
		return miscs.copy(QRect(231, 209, 32, 32));

	else if (id == "box-coin-0")
		return miscs.copy(box_coin);
	else if (id == "box-coin-1")
		return miscs.copy(moveRight(box_coin, 24));
	else if (id == "box-coin-2")
		return miscs.copy(moveRight(box_coin, 13));
	else if (id == "box-coin-3")
		return miscs.copy(box_coin);

	else if (id == "coin-0")
		return miscs.copy(QRect(334, 100, 14, 16));
	else if (id == "coin-1")
		return miscs.copy(QRect(353, 100, 14, 16));
	else if (id == "coin-2")
		return miscs.copy(QRect(370, 100, 14, 16));

	else if (id == "mushroom-red")
		return miscs.copy(QRect(156, 121, 16, 16));
	else if (id == "leaf")
		return miscs.copy(QRect(179, 121, 20, 16));
	else if (id == "tanooki")
		return miscs.copy(QRect(288, 144, 16, 16));

	else if (id == "terrain-L")
		return stage_tiles.copy(terrain);
	else if (id == "terrain-C")
		return stage_tiles.copy(moveBy(terrain, 1, 0));
	else if (id == "terrain-R")
		return stage_tiles.copy(moveBy(terrain, 2, 0));

	else if (id == "Ice-blu")
		return stage_tiles.copy(1208, 52, 16, 16);

	else if (id == "StarBackground")
		return stage_tiles.copy(681, 188, 16, 16);

	else if (id == "cloud-0")
		return miscs.copy(QRect(237, 7, 32, 18));
	else if (id == "cloud-1")
		return stage_tiles.copy(QRect(902, 23, 16, 11));

	else if (id == "black-0")
		return stage_tiles.copy(QRect(698, 35, 16, 16));
	else if (id == "black-1")
		return stage_tiles.copy(QRect(698, 86, 16, 16));
	else if (id == "black-2")
		return stage_tiles.copy(QRect(749, 69, 16, 16));
	else if (id == "black-3")
		return stage_tiles.copy(QRect(766, 69, 16, 16));
	else if (id == "black-4")
		return stage_tiles.copy(QRect(783, 69, 16, 16));
	else if (id == "black-5")
		return stage_tiles.copy(QRect(749, 86, 16, 16));
	else if (id == "black-6")
		return stage_tiles.copy(QRect(766, 86, 16, 16));
	else if (id == "black-7")
		return stage_tiles.copy(QRect(783, 86, 16, 16));
	else if (id == "black-8")
		return stage_tiles.copy(QRect(650, 106, 26, 26));

	else if (id == "donut-block")
		return stage_tiles.copy(QRect(1106, 1, 16, 16));
	else if (id == "shake-0")
		return stage_tiles.copy(QRect(1107, 1, 16, 16));
	else if (id == "shake-1")
		return stage_tiles.copy(QRect(1106, 1, 16, 16));
	else if (id == "shake-2")
		return stage_tiles.copy(QRect(1105, 1, 16, 16));

	else if (id == "tiger-block")
		return stage_tiles.copy(QRect(1004, 18, 16, 16));

	else if (id == "main-screen")
		return title_screen.copy(QRect(516, 226, 16 * 16, 15 * 16));

	else if (id == "pipe-NW")
		return stage_tiles.copy(moveBy(pipe, 0, 0));
	else if (id == "pipe-NE")
		return stage_tiles.copy(moveBy(pipe, 1, 0));
	else if (id == "pipe-W")
		return stage_tiles.copy(moveBy(pipe, 0, 1));
	else if (id == "pipe-E")
		return stage_tiles.copy(moveBy(pipe, 1, 1));
	else if (id == "pipe-NW-gray")
		return stage_tiles.copy(QRect(1, 171, 16, 16));
	else if (id == "pipe-NE-gray")
		return stage_tiles.copy(QRect(18, 171, 16, 16));
	else if (id == "pipe-W-gray")
		return stage_tiles.copy(QRect(1, 188, 16, 16));
	else if (id == "pipe-E-gray")
		return stage_tiles.copy(QRect(18, 188, 16, 16));

	else if (id == "brick")
		return stage_tiles.copy(brick);
	else if (id == "brick-1")
		return stage_tiles.copy(moveBy(brick, 1, 0));
	else if (id == "brick-2")
		return stage_tiles.copy(moveBy(brick, 2, 0));
	else if (id == "brick-3")
		return stage_tiles.copy(moveBy(brick, 3, 0));
	else if (id == "brick_debris")
		return stage_tiles.copy(brick_debris);

	if (id == "roulette-0")
		return card.copy(QRect(258, 350, 16, 16));
	else if (id == "roulette-1")
		return card.copy(QRect(278, 350, 16, 16));
	else if (id == "roulette-2")
		return card.copy(QRect(298, 350, 16, 16));
	else if (id == "star-0")
		return card.copy(QRect(297, 373, 16, 16));
	else if (id == "star-1")
		return card.copy(QRect(344, 374, 16, 16));
	else if (id == "star-2")
		return card.copy(QRect(484, 384, 16, 16));
	else if (id == "flower-0")
		return card.copy(QRect(277, 374, 16, 16));
	else if (id == "flower-1")
		return card.copy(QRect(329, 375, 16, 16));
	else if (id == "flower-2")
		return card.copy(QRect(484, 384, 16, 16));
	else if (id == "mushroom-0")
		return card.copy(QRect(257, 373, 16, 16));
	else if (id == "mushroom-1")
		return card.copy(QRect(316, 375, 16, 16));
	else if (id == "mushroom-2")
		return card.copy(QRect(484, 384, 16, 16));
	else if (id == "star-hud")
		return hud.copy(QRect(235, 33, 24, 28));
	else if (id == "mushroom-hud")
		return hud.copy(QRect(187, 33, 24, 28));
	else if (id == "flower-hud")
		return hud.copy(QRect(211, 33, 24, 28));

	else if (id == "biteplant-0")
		return enemies.copy(QRect(112, 240, 16, 32));
	else if (id == "biteplant-1")
		return enemies.copy(QRect(96, 240, 16, 32));
	else if (id == "fireplant-0")
		return enemies.copy(QRect(128, 144, 16, 32));
	else if (id == "fireplant-1")
		return enemies.copy(QRect(144, 144, 16, 32));
	else if (id == "fireplant-2")
		return enemies.copy(QRect(160, 144, 16, 32));
	else if (id == "fireplant-3")
		return enemies.copy(QRect(176, 144, 16, 32));

	else if (id == "fire-ball-0")
		return enemies.copy(QRect(164, 176, 8, 16));
	else if (id == "fire-ball-1")
		return enemies.copy(QRect(180, 176, 8, 16));
	else if (id == "fire-ball-2")
		return enemies.copy(QRect(164, 192, 8, 16));
	else if (id == "fire-ball-3")
		return enemies.copy(QRect(180, 192, 8, 16));

	else if (id == "flame")
		return enemies.copy(QRect(281, 512, 7, 16));

	else if (id == "hud")
		return hud.copy(hud_panel);

	else if (id == "number-0")
		return hud.copy(QRect(33, 32, 8, 7));
	else if (id == "number-1")
		return hud.copy(QRect(43, 32, 8, 7));
	else if (id == "number-2")
		return hud.copy(QRect(53, 32, 8, 7));
	else if (id == "number-3")
		return hud.copy(QRect(63, 32, 8, 7));
	else if (id == "number-4")
		return hud.copy(QRect(73, 32, 8, 7));
	else if (id == "number-5")
		return hud.copy(QRect(83, 32, 8, 7));
	else if (id == "number-6")
		return hud.copy(QRect(93, 32, 8, 7));
	else if (id == "number-7")
		return hud.copy(QRect(103, 32, 8, 7));
	else if (id == "number-8")
		return hud.copy(QRect(113, 32, 8, 7));
	else if (id == "number-9")
		return hud.copy(QRect(123, 32, 8, 7));
	else if (id == "mario")
		return hud.copy(QRect(8, 43, 16, 7));
	else if (id == "point-100")
		return point.copy(QRect(60, 88, 13, 10));
	else if (id == "point-200")
		return point.copy(QRect(74, 88, 14, 10));
	else if (id == "point-1000")
		return point.copy(QRect(119, 88, 17, 10));

	else if (id == "star-hud")
		return hud.copy(QRect(235, 33, 24, 28));
	else if (id == "mushroom-hud")
		return hud.copy(QRect(187, 33, 24, 28));
	else if (id == "flower-hud")
		return hud.copy(QRect(211, 33, 24, 28));

	else if (id == "stage-clear")
		return card.copy(QRect(65, 370, 116, 15));
	else if (id == "got-a-card")
		return card.copy(QRect(51, 397, 115, 9));

	else if (id == "arrow")
		return hud.copy(QRect(3, 33, 8, 7));
	else if (id == "max-speed")
		return hud.copy(QRect(12, 33, 15, 7));

	else if (id == "hit-0")
		return mario.copy(QRect(379, 19, 16, 16));
	else if (id == "hit-1")
		return mario.copy(QRect(397, 19, 16, 16));
	else if (id == "hit-2")
		return mario.copy(QRect(379, 1, 16, 16));
	else if (id == "hit-3")
		return mario.copy(QRect(397, 1, 16, 16));

	else
		return QPixmap();
}