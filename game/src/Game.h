#ifndef GAME_H
#define	GAME_H

#include <phantom.h>
#include <deque>
#include <glut/GLUTDriver.h>
#include "GameException.h"
#include <sstream>
#include <sharedlib/models/PlayerModel.h>
#include "Settings.h"
#include "networking/LocalRegistry.h"

using namespace std;
using namespace phantom;

class ClientWorld;
class Loader;
class Network;
class KeyboardListener;

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

    KeyboardListener *keyboardListener() { return _keyboardListener; }

    LocalRegistry localRegistry;
private:
    KeyboardListener *_keyboardListener;
};

#endif	/* GAME_H */

