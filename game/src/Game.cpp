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
    Services::settings.loadFromFile("example.json");

    setDriver(new GLUTDriver(this));

    loader      = new Loader();
    world       = new ClientWorld();
    menu        = new MenuState();
    cursor      = new Cursor();
    dedicated   = new Dedicated(*this);
    master      = new Master(*this);
    world->doUpdate = true;
    world->doRender = false;
    menu->doRender  = false;
    menu->doUpdate  = false;

    pushGameState(menu);

    addComponent(cursor);

    // Nest this behind a splash:
    addComponent(master);
    master->init();
}

Game::~Game(){
    delete loader;
    delete world;
    delete menu;
    delete dedicated; dedicated = nullptr;
    NetworkRegistry::destroy();
}

void Game::launchLoader() {

    addComponent(dedicated);
    dedicated->init();

    // Couple the broadcast service:
    Services::setBroadcast(dedicated);
}

// NB: "Master" calls this when it's either connected, or when the connection
// fails.
void Game::launchMenu() {
    // TODO: hide splashscreen.

    menu->doRender  = true;
    menu->doUpdate  = true;

    if(master->isConnected()) {
        cout << "Connected to master server." << endl;

        // Places an asynchronized call. TODO: add lambda to handle the response,
        // in the master constructor.
        master->requestAvailableDedicated();
    } else {
        // Master connection failed. Show something in the GUI here?
        cout << "Unable to connect to master server. Loading menu anyway." << endl;
    }
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