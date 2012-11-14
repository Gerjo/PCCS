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
#include <sharedlib/services/Services.h>
#include "components/Cursor.h"

using namespace std;
using namespace phantom;

class ClientWorld;
class Loader;
class Network;
class MenuState;

class Game : public PhantomGame {
public:
    Game(const char* configfile);
    virtual ~Game();
    void update(Time time);
    void startPlaying(void);

    ClientWorld* world;
    MenuState* menu;
    Loader* loader;

    Cursor* cursor;

    Network* network;
    PlayerModel me; // This is the person behind the PC.

    LocalRegistry localRegistry;
};

#endif	/* GAME_H */

