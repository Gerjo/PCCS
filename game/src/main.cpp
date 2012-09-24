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

    phantom::BaseDriver* base = new phantom::GLUTDriver();

    game->start(argc, argv, base);

	delete game;
    delete base;
	return 0;
}