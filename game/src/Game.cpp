#include "Game.h"
#include <iostream>

#include <input/KeyboardListener.h>
#include "gamestates/ClientWorld.h"
#include "gamestates/Loader.h"
#include "gamestates/MenuState.h"
#include "networking/Network.h"
#include "guicomponents/InputField.h"

using namespace std;

//#define SPARKIE

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));
    
    loader      = new Loader();
    world       = new ClientWorld();
    menu        = new MenuState();
    network     = new Network(*this);
    cursor      = new Cursor();

    world->doUpdate = true;
    world->doRender = false;

#ifdef SPARKIE
    pushGameState(menu);
#else
    pushGameState(loader);

    // Couple the broadcast service:
    addComponent(network);
    network->init();
    Services::setBroadcast(network);
#endif

    addComponent(cursor);
}

Game::~Game(){
    delete loader;
    delete world;
    delete menu;

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