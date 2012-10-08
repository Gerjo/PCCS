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
#include "components/Selector.h"
#include "gameobjects/Soldier.h"
#include "components/RtsCamera.h"
#include <glut/GLUTDriver.h>
#include "FixedLayer.h"
#include "ObjectFactory.h"
#include <fstream>

#include "pathfinding/BSPTree.h"

#include "json/reader.h"

using namespace std;
using namespace phantom;

class RtsCamera;

class Game : public PhantomGame {
public:
    Game(const char* configfile);
    virtual ~Game();

    RtsCamera& getRtsCamera(void);

    void parseJson();

private:
    GameState _gameState;

    Layer _gridLayer;
    Layer _cursorlayer;
    EntityLayer _gameObjects;

    FixedLayer* _fixedLayer;

    BSPTree* _tree;

    Selector* _selector;
    RtsCamera* _rtsCamera;

    void createGrid(void);
    void addSoldiers(void);
};

#endif	/* GAME_H */

