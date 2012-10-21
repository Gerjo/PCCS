#include "Game.h"
#include <iostream>
#include <fstream>
#include "components/RtsCamera.h"
#include "gameobjects/Tree.h"
#include "pathfinding/Pathfinding.h"
#include "gameobjects/Enemy.h"
#include <input/Input.h>
#include "gamestates/World.h"
#include "gamestates/Loader.h"
#include "networking/Network.h"

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));

    preloader = new Loader();
    preloader->init();
    pushGameState(preloader);

    preloader->addText("It works! And that is an assumption. -- Gerjo");

    addComponent(network = new Network(*this));
    network->init();

    //world = new World();
    //world->init();
    //pushGameState(world);
}

Game::~Game(){
    delete preloader;
    //delete world;
}

void Game::update(float elapsed) {
    PhantomGame::update(elapsed);

    // Allows us to quick exit the game.
    if(getDriver()->getInput()->getKeyboardState()->isKeyDown(27)) {
        this->_running = false;
    }
}

RtsCamera& Game::getRtsCamera(void) {
    return *(world->camera);
}

Cursor* Game::getCursor(void) {
    return world->cursor;
}

Pathfinding* Game::getPathfinding() {
    return world->pathfinding;
}

BSPTree* Game::getTree(void) {
    return world->tree;
}