#ifndef PLAYING_H
#define	PLAYING_H

#include <phantom.h>
#include "../ObjectFactory.h"
#include <sharedlib/rapidjson/document.h>
#include <sharedlib/rapidjson/reader.h>
#include <fstream>

using namespace phantom;

class FixedLayer;
class BSPTree;
class Pathfinding;
class RtsCamera;
class Selector;
class Cursor;
class Console;

class World : public GameState {

public:
    World();
    virtual ~World();

    void init(void);

    // Layers:
    FixedLayer* fixedLayer;
    BSPTree* tree;
    Layer* overlay;

    // Components:
    Pathfinding* pathfinding;
    RtsCamera* camera;
    Selector* selector;
    Cursor* cursor;
    Console* console;
private:
    void addSoldiers(void);
    void loadJson(void);
};

#endif	/* PLAYING_H */

