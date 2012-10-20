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
class World;
class Loader;

class Game : public PhantomGame {
public:
    Game(const char* configfile);
    virtual ~Game();
    void update(float elapsed);

    // TODO: get rid of this:
    RtsCamera& getRtsCamera(void);
    Pathfinding* getPathfinding(void);
    Cursor* getCursor(void);
    Layer* getBulletLayer(void);
    BSPTree* getTree(void);

    // Gamestates:
    World* world;
    Loader* preloader;
private:

};

#endif	/* GAME_H */

