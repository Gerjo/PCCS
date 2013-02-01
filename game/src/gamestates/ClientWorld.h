#ifndef PLAYING_H
#define	PLAYING_H

#include <sstream>
#include <cstdlib>
#include <phantom.h>
#include "../gameobjects/HeavyFactory.h"
#include <sharedlib/serialization/Data.h>
#include <sharedlib/CommandQueue.h>
#include <sharedlib/missions/Mission.h>
#include <sharedlib/missions/ObjDestroy.h>
#include <core/Console.h>

using namespace phantom;

using std::stringstream;
using std::string;
using std::cout;
using std::endl;

class Selector;
class ScrollBehaviour;
class FixedLayer;
class BSPTree;
class Cursor;
class HUD;

#ifdef _DEBUG
    class Procedural;
#endif

class ClientWorld : public GameState {

public:
    ClientWorld();
    virtual ~ClientWorld();

    void start(void);
    void load(string json);
    void push(string json);
    virtual void update(const PhantomTime& time);
#ifdef _DEBUG
    Procedural* getProcedural();
#endif

    BSPTree* gameobjects;
    Layer* fixedlayer;

    Camera* camera;
    Selector* selector;
    HUD* hud;
    Mission* mission;
    ObjDestroy* obj;
private:
    CommandQueue _commands;
#ifdef _DEBUG
    Procedural* _procedural;
#endif
};

#endif	/* PLAYING_H */

