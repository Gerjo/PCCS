#include <iostream>

#include "Game.h"

using namespace std;

#include <phantom.h>
#include <graphics/GLUTRenderer.h>
#include <input/GLUTInputState.h>

int main(int argc, char *argv[]) {
	phantom::PhantomGame	*game		=	new phantom::PhantomGame("settings.yaml");
	phantom::Renderer		*renderer	=	new phantom::GLUTRenderer(800, 600);
	phantom::InputState		*input		=	new phantom::GLUTInputState();

	game->setRenderer(renderer);
	game->addComponent(input);

	game->start(argc, argv);

	delete input;
	delete renderer;
	delete game;

	return 0;
}