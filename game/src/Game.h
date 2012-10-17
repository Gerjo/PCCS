#ifndef GAME_H
#define	GAME_H

#include <phantom.h>
#include <deque>
#include "gameobjects/Soldier.h"
#include "gameobjects/Tree.h"
#include "tiles/TiledObjectLayer.h"
#include "components/Selector.h"
#include "gameobjects/Soldier.h"
#include "components/RtsCamera.h"
#include <glut/GLUTDriver.h>
#include "FixedLayer.h"
#include "ObjectFactory.h"
#include "GameException.h"
#include <fstream>
#include <sstream>

#include "pathfinding/BSPTree.h"

#include <rapidjson/document.h>
#include <rapidjson/reader.h>
#include "pathfinding/Pathfinding.h"
#include "components/Cursor.h"
#include "components/Console.h"

using namespace std;
using namespace phantom;

class RtsCamera;

class Game : public PhantomGame {
public:
    Game(const char* configfile);
    virtual ~Game();
    RtsCamera& getRtsCamera(void);
    void parseJson(void);
    void update(float elapsed);
    Pathfinding* getPathfinding(void);
    Cursor* getCursor(void);
    Layer* getBulletLayer(void);

private:
    GameState *_gameState;
    Layer *_gridLayer;
    Layer *_cursorlayer;
    Layer *_bulletLayer;
    EntityLayer *_gameObjects;
    FixedLayer* _fixedLayer;
    BSPTree* _tree;
    Selector* _selector;
    RtsCamera* _rtsCamera;
    Pathfinding* _pathfinding;
    Cursor* _cursor;
    Console* _console;

    void addSoldiers(void);
    void addGameObject(Composite* comp);
};

#endif	/* GAME_H */

