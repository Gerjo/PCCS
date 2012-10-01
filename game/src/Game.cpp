#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    _tiles.createTiles(10, 20, 10);

    int tileSize = 10;
    int width    = 800;
    int height   = 600;

    for(int x = 0; x < width; x += tileSize) {
        for(int y = 0; y < height; y += tileSize) {
            Ground* ground = new Ground();

            ground->setX(x);
            ground->setY(y);
            
            _tiles.addComponent(ground);
        }
    }

    _gameState.addComponent(&_tiles);

    pushGameState(&_gameState);
}
