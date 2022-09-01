#pragma once

#include <QGraphicsScene>
#include <string>
#include <QList>

#include "Mario.h"

using namespace std;

class LevelManager
{

    public:

        // load all items from the given level in the given scene
        // also returns the Mario object
        static Mario* load(string level_name, QGraphicsScene* scene, bool _big = false, bool _raccoon = false, bool _tanooki = false);
};
