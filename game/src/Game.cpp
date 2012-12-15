#include "Game.h"
#include <iostream>

#include <input/KeyboardListener.h>
#include "gamestates/ClientWorld.h"
#include "gamestates/Loader.h"
#include "gamestates/MenuState.h"
#include "networking/Dedicated.h"
#include "guicomponents/InputField.h"
#include "networking/Master.h"

#include <functional>

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    Services::settings()->loadFromFile("conf/settings.json");

    setDriver(new GLUTDriver(this));

    loader      = new Loader();
    world       = nullptr;
    menu        = new MenuState();
    cursor      = new Cursor();
    dedicated   = new Dedicated(*this);
    master      = new Master(*this);
    menu->doRender  = false;
    menu->doUpdate  = false;

    std::function<void(string args)> command = [this] (string args) {

        this->dedicated->destroy();
        this->dedicated = new Dedicated(*this);
        addComponent(this->dedicated);

        DedicatedModel tmpModel;
        tmpModel.ipv4 = args;
        tmpModel.name = "";
        tmpModel.port = 8070;
        tmpModel.lastPing = 99;

        getGame<Game*>()->dedicated->init(tmpModel);
        getGame<Game*>()->launchLoader();
    };

    Console::mapCommand("connect", command);

    pushGameState(menu);

    addComponent(dedicated);
    addComponent(cursor);

    // Nest this behind a splash:
    addComponent(master);
    master->init();
}

Game::~Game(){
    delete loader;
    delete world;
    delete menu;
    NetworkRegistry::destroy();
}

void Game::launchLoader() {
    // Couple the broadcast service:
    Services::setBroadcast(dedicated);

    launchGame();
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

void Game::launchGame(void) {
    world = new ClientWorld();
    popGameState();
    pushGameState(world);
}

void Game::startPlaying(void) {
    world->start();

    world->doUpdate = true;
    world->doRender = true;

    loader->doUpdate = false;
    loader->doRender = false;
}

void Game::update(phantom::PhantomTime time) {
    PhantomGame::update(time);
}