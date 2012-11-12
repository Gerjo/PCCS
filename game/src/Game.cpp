#include "Game.h"
#include <iostream>

#include <input/KeyboardListener.h>
#include "gamestates/ClientWorld.h"
#include "gamestates/Loader.h"
#include "networking/Network.h"
#include "guicomponents/InputField.h"

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));
    
    // Create a keyboard listener instance.
    loader  = new Loader();
    world   = new ClientWorld();
    network = new Network(*this);
    
    loader->init();

    world->doUpdate = true;
    world->doRender = false;

    world->addComponent(this->getConsole());

    pushGameState(loader);
    pushGameState(world);

    addComponent(network);

    network->init();

    // Couple the broadcast service:
    Services::setBroadcast(network);
}

Game::~Game(){
    delete loader;
    delete world;

    NetworkRegistry::destroy();
}

void Game::startPlaying(void) {
    world->start();

    world->doUpdate = true;
    world->doRender = true;

    loader->doUpdate = false;
    loader->doRender = false;
}

void Game::update(Time time) {
    PhantomGame::update(time);
}