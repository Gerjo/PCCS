#include <iostream>

#include "Game.h"

using namespace std;

#include <phantom.h>
#include <graphics/GLUTRenderer.h>
#include <input/GLUTInputState.h>
#include <graphics/GLUTDriver.h>

int main(int argc, char *argv[]) {
    phantom::PhantomGame	*game		=	new phantom::PhantomGame("settings.yaml");
    phantom::GameState* state = new phantom::GameState();
    game->pushGameState(state);
    phantom::Composite* meh = new phantom::Composite();
    meh->getGraphics()->beginPath();
    meh->getGraphics()->setFillStyle(phantom::Color(255,0,0,255));
    meh->getGraphics()->setLineStyle(phantom::Color(0,255,0,255));
    meh->getGraphics()->rect(0.10,0.10,0.25,0.25);
    meh->getGraphics()->beginPath();
    state->addComponent(meh);
    game->start(argc, argv, &phantom::GLUTDriver());

    delete meh;
    delete game;

    return 0;
}