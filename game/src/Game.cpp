#include "Game.h"
#include <iostream>

#include <input/KeyboardListener.h>
#include "gamestates/ClientWorld.h"
#include "gamestates/Loader.h"
#include "gamestates/MenuState.h"
#include "networking/Dedicated.h"
#include "guicomponents/InputField.h"
#include "networking/Master.h"

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));

    loader      = new Loader();
    world       = new ClientWorld();
    menu        = new MenuState();
    cursor      = new Cursor();
    dedicated   = new Dedicated(*this);
    master      = new Master(*this);
    world->doUpdate = true;
    world->doRender = false;

    pushGameState(menu);

    addComponent(cursor);
}

Game::~Game(){
    delete loader;
    delete world;
    delete menu;
    delete dedicated; dedicated = nullptr;
    NetworkRegistry::destroy();
}

void Game::launchLoader() {
    master->init();


    // Couple the broadcast service:
    addComponent(dedicated);
    dedicated->init();
    Services::setBroadcast(dedicated);
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