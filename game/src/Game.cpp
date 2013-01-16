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

    dedicated   = new Dedicated(*this);
    addComponent(dedicated);

    setDriver(new GLDriver(this));

    loader      = nullptr;
    world       = nullptr;
    menu        = nullptr;
    cursor      = new Cursor();
    master      = new Master(*this);

    std::function<void(string args)> command = [this] (string args) {
        this->launchLoader();

        this->dedicated->destroy();
        this->dedicated = new Dedicated(*this);
        
        // Couple the broadcast service:
        Services::setBroadcast(dedicated);
        addComponent(this->dedicated);

        DedicatedModel      tmpModel;
        tmpModel.ipv4       = args;
        tmpModel.name       = "";
        tmpModel.port       = 8070;
        tmpModel.lastPing   = 99;

        getGame<Game*>()->dedicated->init(tmpModel);
    };

    Console::mapCommand("connect", command);

    addComponent(cursor);

    // Nest this behind a splash:
    addComponent(master);
    master->init();

    // Add one camera so we know something can be rendered.
    getDriver()->enableCamera(getDriver()->createCamera());
}

Game::~Game(){
    delete loader;
    delete world;
    delete menu;
    NetworkRegistry::destroy();
}

void Game::launchLoader() {
    popGameState();
    menu->destroy();
    menu            = nullptr;

    loader          = new Loader();
    pushGameState(loader);

    delete world;
    world = new ClientWorld();
    world->doRender = false;
}

// NB: "Master" calls this when it's either connected, or when the connection
// fails.
void Game::launchMenu() {
    menu = new MenuState();
    pushGameState(menu);

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
    popGameState();
    loader->destroy();
    loader = nullptr;

    pushGameState(world);
}

void Game::startPlaying(void) {
    world->doUpdate = true;
    world->doRender = true;

    world->start();
}

void Game::update(phantom::PhantomTime time) {
    PhantomGame::update(time);
}