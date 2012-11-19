#include <phantom.h>
#include <glut/GLUTDriver.h>
#include <yaxl.h>
#include <sharedlib/sharedlib.h>

#include "ProceduralDemo.h"

using namespace phantom;

int main(int argc, char* argv[])
{
    PhantomGame* game = new PhantomGame("");

    game->setDriver(new GLUTDriver(game));
    ProceduralDemo* demo = new ProceduralDemo();
    game->addComponent(demo);
    game->start(argc, argv);
    delete game;

	return 0;
}

