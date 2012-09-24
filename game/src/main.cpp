#include <iostream>

#include "Game.h"

using namespace std;

#include <phantom.h>
#include <graphics/GLUTRenderer.h>
#include <input/GLUTInputState.h>
#include <graphics/GLUTDriver.h>
#include <graphics/BaseDriver.h>

int main(int argc, char *argv[]) {
    phantom::PhantomGame	*game		=	new phantom::PhantomGame("settings.yaml");
    phantom::GameState* state = new phantom::GameState();
    game->pushGameState(state);
    phantom::Composite* meh = new phantom::Composite();
    meh->getGraphics()->beginPath();
    meh->getGraphics()->setFillStyle(phantom::Color(127,0,0,127));
    meh->getGraphics()->setLineStyle(phantom::Color(0,127,0,127));
    meh->getGraphics()->rect(50,50,1180,700);
    meh->getGraphics()->beginPath();
    state->addComponent(meh);

    phantom::BaseDriver* baseDriver = new phantom::GLUTDriver();

    game->start(argc, argv, baseDriver);

    delete meh;
    delete game;

    return 0;
}