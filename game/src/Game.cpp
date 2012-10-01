#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    //_tiles.createTiles(12, 2, 1);

    int tileSize = 12;
    int width    = getWidth();
    int height   = getHeight();

    for(int x = 0; x < width; x += tileSize) {
        for(int y = 0; y < height; y += tileSize) {
            Ground* ground = new Ground();

            ground->setX(x);
            ground->setY(y);

            _tiles.addComponent(ground);
        }
    }

    _tiles.addComponent(new Soldier);

    _gameState.addComponent(&_tiles);

    pushGameState(&_gameState);
}
