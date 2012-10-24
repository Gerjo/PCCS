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


class RtsCamera;
class FixedLayer;
class BSPTree;

class ClientWorld : public GameState {

public:
    ClientWorld();
    virtual ~ClientWorld();

    void init(void);
    void load(string json);
    virtual void update(const float& elapsed);

    BSPTree* gameobjects;
    FixedLayer* fixedlayer;

    RtsCamera* rtsCamera;
    Camera* camera;
private:
    CommandQueue _commands;

};

#endif	/* PLAYING_H */

