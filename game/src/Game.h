#ifndef GAME_H
#define	GAME_H

#include <phantom.h>
#include <deque>
#include <opengl/GLDriver.h>
#include "GameException.h"
#include <sstream>
#include <sharedlib/models/PlayerModel.h>
#include "networking/LocalRegistry.h"
#include <sharedlib/services/Services.h>
#include "components/Cursor.h"

using namespace std;
using namespace phantom;

class ClientWorld;
class Loader;
class Dedicated;
class MenuState;
class Master;

class Game : public PhantomGame {
public:
    Game(const char* configfile);
    virtual ~Game();
    void update(phantom::PhantomTime time);
    void launchLoader();
    void launchMenu();
    void launchGame();

    void startPlaying(void);

    ClientWorld* world;
    MenuState* menu;
    Loader* loader;

    Cursor* cursor;

    Master* master;
    Dedicated* dedicated;
    PlayerModel me; // This is the person behind the PC.

    LocalRegistry localRegistry;
};

#endif	/* GAME_H */

