#ifndef GAME_H
#define	GAME_H

#include <phantom.h>

#include "gameobjects/Soldier.h"
#include "gameobjects/Tank.h"
#include "gameobjects/Water.h"
#include "gameobjects/Tree.h"
#include <layer/TiledObjectLayer.h>
#include "gameobjects/Ground.h"

using namespace phantom;

class Game : public PhantomGame {
public:
    Game(const char* configfile);

private:
    TiledObjectLayer _tiles;
    GameState _gameState;
};

#endif	/* GAME_H */

