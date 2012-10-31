#include "Game.h"
#include <iostream>

#include "components/KeyboardListener.h"
#include "gamestates/ClientWorld.h"
#include "gamestates/Loader.h"
#include "networking/Network.h"
#include "InputField.h"

using namespace std;

Game::Game(const char* configfile) : PhantomGame(configfile) {
    setDriver(new GLUTDriver(this));

    _keyboardListener = new KeyboardListener();
    addComponent(_keyboardListener);

    loader  = new Loader();
    world   = new ClientWorld();
    network = new Network(*this);

    loader->init();
    world->init();

    world->doUpdate = true;
    world->doRender = false;

    InputField *inputField = new InputField(100.0f, 100.0f, 100.0f, 100.0f, Colors::CORNFLOWER);
    inputField->keyboard(_keyboardListener);
    world->addComponent(inputField);

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