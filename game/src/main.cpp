#include <iostream>

#include "Game.h"

using namespace std;

#include <phantom.h>
#include <graphics/GLUTRenderer.h>
#include <input/GLUTInputState.h>
#include <graphics/GLUTDriver.h>
#include <graphics/BaseDriver.h>

int main(int argc, char *argv[]) {
    phantom::PhantomGame* game		=	new phantom::PhantomGame("settings.yaml");
    phantom::GameState* state = new phantom::GameState();
    game->pushGameState(state);
    phantom::Composite* meh = new phantom::Composite();
    meh->getGraphics()->beginPath();
    meh->getGraphics()->setFillStyle(phantom::Color(127,0,0,127));
    meh->getGraphics()->setLineStyle(phantom::Color(0,127,0,127));

    meh->getGraphics()->arc(500,250,100,0,static_cast<float>((2*M_PI)));

    /*for(unsigned int i = 0; i < 128; ++i)
    {
        for(unsigned int j = 0; j < 72; ++j)
        {
            meh->getGraphics()->line(i*50, 0, i*50, j*50);
            meh->getGraphics()->line(0, j*50, i*50, j*50);
        }
    }*/

    meh->getGraphics()->beginPath();
    state->addComponent(meh);

    phantom::BaseDriver* baseDriver = new phantom::GLUTDriver();

    game->start(argc, argv, baseDriver);

    delete meh;
    delete game;

    return 0;
}