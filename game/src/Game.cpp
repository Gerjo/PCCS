#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    pushGameState(&_gameState);

    Soldier* soldier = new Soldier();
    _gameState.addComponent(soldier);

    Composite* composite = new Tank();
    _gameState.addComponent(composite);

    Composite* tree = new Tree();
    _gameState.addComponent(tree);

    Composite* water = new Water();
    _gameState.addComponent(water);
}
