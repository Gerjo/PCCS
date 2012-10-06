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
#include "RtsCamera.h"
#include <glut/GLUTDriver.h>
#include "FixedLayer.h"
#include "ObjectFactory.h"

using namespace std;
using namespace phantom;

class RtsCamera;

class Game : public PhantomGame {
public:
    Game(const char* configfile);
    virtual ~Game();

    RtsCamera& getRtsCamera(void);

private:
    GameState _gameState;

    Layer _gridLayer;
    Layer _cursorlayer;
    EntityLayer _gameObjects;

    FixedLayer* _fixedLayer;


    Selector* _selector;
    RtsCamera* _rtsCamera;

    void createGrid(void);
    void addSoldiers(void);
};

#endif	/* GAME_H */

