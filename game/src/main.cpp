#include <iostream>

#include "Game.h"

using namespace std;

#include <phantom.h>
#include <graphics/GLUTRenderer.h>
#include <input/GLUTInputState.h>
#include <graphics/GLUTDriver.h>

int main(int argc, char *argv[]) {
	phantom::PhantomGame	*game		=	new phantom::PhantomGame("settings.yaml");
	//game->setRenderer(renderer);
	//game->addComponent(input);

    game->start(argc, argv, &phantom::GLUTDriver());

	delete game;

	return 0;
}