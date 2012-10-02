#ifndef GAME_H
#define	GAME_H

#include <phantom.h>

#include "gameobjects/Soldier.h"
#include "gameobjects/Tank.h"
#include "gameobjects/Water.h"
#include "gameobjects/Tree.h"
#include "gameobjects/Ground.h"

#include "Selector.h"

using namespace phantom;

class Game : public PhantomGame {
public:
    Game(const char* configfile);

private:
    TiledObjectLayer _tiles;
    RenderLayer _cursorlayer;
    GameState _gameState;
    Selector _selector;

};

#endif	/* GAME_H */

