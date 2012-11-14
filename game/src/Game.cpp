#include "Game.h"
#include <iostream>

#include <input/KeyboardListener.h>
#include "gamestates/ClientWorld.h"
#include "gamestates/Loader.h"
#include "gamestates/MenuState.h"
#include "networking/Network.h"
#include "guicomponents/InputField.h"

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));
    
    loader      = new Loader();
    world       = new ClientWorld();
    menu        = new MenuState();
    network     = new Network(*this);

    world->doUpdate = true;
    world->doRender = false;

    pushGameState(loader);
    pushGameState(world);
    addComponent(network);

    network->init();

    // Couple the broadcast service:
    Services::setBroadcast(network);

    // Must remain at bottom.
    addComponent(this->getConsole());
}

Game::~Game(){
    delete loader;
    delete world;

    NetworkRegistry::destroy();
}

void Game::startPlaying(void) {
    //popGameState();
    //pushGameState(world);
    world->start();

    world->doUpdate = true;
    world->doRender = true;

    loader->doUpdate = false;
    loader->doRender = false;
}

void Game::update(Time time) {
    PhantomGame::update(time);
}