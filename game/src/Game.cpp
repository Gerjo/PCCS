#include "Game.h"
#include <iostream>

#include "components/KeyboardListener.h"
#include "gamestates/ClientWorld.h"
#include "gamestates/Loader.h"
#include "networking/Network.h"
#include "guicomponents/InputField.h"

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));

    // Create a keyboard listener instance.
    new KeyboardListener(getDriver(), getPhantomGame());

    loader  = new Loader();
    world   = new ClientWorld();
    network = new Network(*this);

    loader->init();

    world->doUpdate = true;
    world->doRender = false;

    Console *console = new Console();
    world->addComponent(console);

    for(int i = 0; i < 5; ++i) console->addLog("Blaat");

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
    delete KeyboardListener::INSTANCE;

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