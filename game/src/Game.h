#ifndef GAME_H
#define	GAME_H

#include <phantom.h>
#include <deque>
#include <glut/GLUTDriver.h>
#include "GameException.h"
#include <sstream>


using namespace std;
using namespace phantom;

class World;
class Loader;
class Network;

class Game : public PhantomGame {
public:
    Game(const char* configfile);
    virtual ~Game();
    void update(float elapsed);

    // Gamestates:
    World* world;
    Loader* loader;

    Network* network;

    void startPlaying(void);
private:

};

#endif	/* GAME_H */

