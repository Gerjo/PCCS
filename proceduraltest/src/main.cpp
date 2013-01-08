#include <phantom.h>
#include <opengl/GLDriver.h>
#include <Procedural.h>

using namespace phantom;

void main(int argc, char *argv[]) {
	PhantomGame game("");
	game.setDriver(new GLDriver(&game));
    game.getDriver()->enableCamera(game.getDriver()->createCamera());
	GameState *state = new GameState();
	game.addComponent(state);
	
	Procedural *proc = new Procedural();
	game.addComponent(proc);
    proc->generateWorld(1920,1080,4,1000);
    proc->paint();
	
	game.start(argc, argv);
}