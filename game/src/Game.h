#ifndef GAME_H
#define	GAME_H

#ifdef WIN32
    #ifdef _DEBUG
        #define _CRTDBG_MAP_ALLOC
        #include <stdlib.h>
        #include <crtdbg.h>
    #endif /* Debug */
#endif /* win32*/

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

#include "pathfinding/BSPTree.h"

#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "pathfinding/Pathfinding.h"
#include "components/Cursor.h"

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

private:
    GameState *_gameState;
    Layer *_gridLayer;
    Layer *_cursorlayer;
    EntityLayer *_gameObjects;
    FixedLayer* _fixedLayer;
    BSPTree* _tree;
    Selector* _selector;
    RtsCamera* _rtsCamera;
    Pathfinding* _pathfinding;
    Cursor* _cursor;

    void addSoldiers(void);
    void addGameObject(Composite* comp);
};

#endif	/* GAME_H */

