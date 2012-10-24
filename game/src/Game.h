#ifndef GAME_H
#define	GAME_H

#include <phantom.h>
#include <deque>
#include "gameobjects/Soldier.h"
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

#include <sharedlib/rapidjson/document.h>
#include <sharedlib/rapidjson/reader.h>
#include "pathfinding/Pathfinding.h"
#include "components/Cursor.h"
#include "components/Console.h"

using namespace std;
using namespace phantom;

class RtsCamera;
class World;
class Loader;
class Network;

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

    Network* network;
private:

};

#endif	/* GAME_H */

