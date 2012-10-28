#ifndef GAME_H
#define	GAME_H

#include <phantom.h>
#include <deque>
#include <glut/GLUTDriver.h>
#include "GameException.h"
#include <sstream>
#include <sharedlib/models/PlayerModel.h>
#include "Settings.h"

using namespace std;
using namespace phantom;

class ClientWorld;
class Loader;
class Network;

class Game : public PhantomGame {
public:
    Game(const char* configfile);
    virtual ~Game();
    void update(Time time);
    void startPlaying(void);

    ClientWorld* world;
    Loader* loader;
    Network* network;
    PlayerModel me; // This is the person behind the PC.

private:

};

#endif	/* GAME_H */

