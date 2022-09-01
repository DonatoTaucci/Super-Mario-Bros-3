#include <QApplication>

#include "Sprites.h"
#include "Sounds.h"
#include "Game.h"

int main(int argc, char *argv[])
{
    // create Qt application
    QApplication app(argc, argv);

	// instance sprites and sounds
	Sprites::instance();
	Sounds::instance();

	// create and show the game
	Game::instance()->show();

    // launch Qt event loop
    return app.exec();
}
