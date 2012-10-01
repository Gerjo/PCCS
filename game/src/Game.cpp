#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    _gameState.addComponent(&_tiles);
    _tiles.createTiles(10,5,5);
    pushGameState(&_gameState);

    _tiles.addComponent(new Soldier());
    _tiles.addComponent(new Tank());
    _tiles.addComponent(new Tree());
    _tiles.addComponent(new Water());
}
