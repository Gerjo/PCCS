#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    pushGameState(&_gameState);


    Soldier* soldier = new Soldier();
    _gameState.addComponent(soldier);
}
