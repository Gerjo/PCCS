#ifndef PLAYING_H
#define	PLAYING_H

#include <sstream>
#include <cstdlib>
#include <phantom.h>
#include "../gameobjects/HeavyFactory.h"
#include <sharedlib/serialization/Data.h>
#include <sharedlib/CommandQueue.h>

using namespace phantom;

using std::stringstream;
using std::string;
using std::cout;
using std::endl;


class Selector;
class RtsCamera;
class FixedLayer;
class BSPTree;
class Cursor;

class ClientWorld : public GameState {

public:
    ClientWorld();
    virtual ~ClientWorld();

    void init(void);
    void load(string json);
    void push(string json);
    virtual void update(const Time& time);

    BSPTree* gameobjects;
    FixedLayer* fixedlayer;

    RtsCamera* rtsCamera;
    Camera* camera;
    Selector* selector;
    Cursor* cursor;
private:
    CommandQueue _commands;

};

#endif	/* PLAYING_H */

