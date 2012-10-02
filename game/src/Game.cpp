#include "Game.h"
#include <iostream>

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    _tiles.createTiles(12, 200, 100);

    int tileSize = 12;
    int width    = getWidth();
    int height   = getHeight();

    for(int y = 0; y < height; y += tileSize) {
        for(int x = 0; x < width; x += tileSize) {
            Ground* ground = new Ground();

            ground->setX(static_cast<float>(x));
            ground->setY(static_cast<float>(y));

            _tiles.addComponent(ground);
        }
    }

    _tiles.addComponent(new Soldier);
    _gameState.addComponent(&_tiles);

    pushGameState(&_gameState);
}
