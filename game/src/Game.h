#ifndef GAME_H
#define	GAME_H

#include <phantom.h>

#include "Soldier.h"

using namespace phantom;

class Game : public PhantomGame {
public:
    Game(const char* configfile);
private:

    GameState _gameState;
};

#endif	/* GAME_H */

