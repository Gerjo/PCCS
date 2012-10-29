#include "Game.h"
#include <iostream>

#include "components/KeyboardListener.h"
#include "gamestates/ClientWorld.h"
#include "gamestates/Loader.h"
#include "networking/Network.h"

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));

    addComponent(new KeyboardListener());

    loader  = new Loader();
    world   = new ClientWorld();
    network = new Network(*this);

    loader->init();
    world->init();

    world->doUpdate = true;
    world->doRender = false;

    pushGameState(loader);
    pushGameState(world);

    addComponent(network);

    network->init();
}

Game::~Game(){
    delete loader;
    delete world;
}

void Game::startPlaying(void) {
    world->doUpdate = true;
    world->doRender = true;

    loader->doUpdate = false;
    loader->doRender = false;
}

void Game::update(Time time) {
    PhantomGame::update(time);
}