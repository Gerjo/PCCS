#ifndef GAME_H
#define	GAME_H

#include <phantom.h>
#include <deque>
#include "gameobjects/Soldier.h"
#include "gameobjects/Tank.h"
#include "gameobjects/Water.h"
#include "gameobjects/Tree.h"
#include "gameobjects/Ground.h"
#include "tiles/TiledObjectLayer.h"
#include "Selector.h"
#include "gameobjects/Soldier.h"

using namespace std;
using namespace phantom;
using namespace Eigen;

class Game : public PhantomGame {
public:
    Game(const char* configfile);

private:
    TiledObjectLayer _tiles;
    RenderLayer _cursorlayer;
    GameState _gameState;
    Selector _selector;

    deque<Soldier*> _soldiers;
};

#endif	/* GAME_H */

