#ifndef PLAYING_H
#define	PLAYING_H

#include <sstream>
#include <cstdlib>
#include <phantom.h>
#include <sharedlib/factories/HeavyFactory.h>
#include <sharedlib/serialization/Data.h>
#include <sharedlib/CommandQueue.h>

using namespace phantom;

using std::stringstream;
using std::string;
using std::cout;
using std::endl;


class RtsCamera;
class FixedLayer;

class World : public GameState {

public:
    World();
    virtual ~World();

    void init(void);
    void load(string json);
    virtual void update(const float& elapsed);

    Layer* gameobjects;
    FixedLayer* fixedlayer;

    RtsCamera* rtsCamera;
    Camera* camera;
private:
    CommandQueue _commands;

};

#endif	/* PLAYING_H */

