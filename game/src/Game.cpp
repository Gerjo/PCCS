#include "Game.h"
#include <iostream>
#include "RtsCamera.h"


using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));
    cout << "It works! And that is an assumption. -- Gerjo" << endl;

    pushGameState(&_gameState);



    _gameState.addComponent(&_gridLayer);
    _gameState.addComponent(&_gameObjects);
    _gameState.addComponent(&_cursorlayer);

    _fixedLayer = new FixedLayer();
    _fixedLayer->addComponent(_rtsCamera = new RtsCamera());
    _fixedLayer->addComponent(_selector = new Selector());
    _gameState.addComponent(_fixedLayer);

    createGrid();
    addSoldiers();

    cout << " end constructor " << endl;
}

Game::~Game(){
    delete getDriver();
}

void Game::addSoldiers(void) {
    for(float i = 1; i <= 20; ++i) {
        Soldier* soldier = new Soldier();
        soldier->setX(i * 30);
        soldier->setY(i * 30);
        soldier->setTarget(soldier->getPosition());

        _selector->addSoldier(soldier);

        _gameObjects.addComponent(soldier);
    }
}

void Game::createGrid(void) {
    int tileSize = 50;
    int width    = 2000; // getWidth();
    int height   = 1000; //getHeight();

    for(int y = 0; y < height - tileSize; y += tileSize) {
        for(int x = 0; x < width - tileSize; x += tileSize) {
            Ground* ground = new Ground();

            ground->setX(static_cast<float>(x));
            ground->setY(static_cast<float>(y));

            _gridLayer.addComponent(ground);
        }
    }
}

RtsCamera& Game::getRtsCamera(void) {
    return *_rtsCamera;
}
