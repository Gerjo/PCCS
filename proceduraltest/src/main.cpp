#include <phantom.h>
#include <opengl/GLDriver.h>
#include <Procedural.h>

using namespace phantom;

void main(int argc, char *argv[]) {
	PhantomGame game("");
	game.setDriver(new GLDriver(&game));
	
	GameState *state = new GameState();
	game.addComponent(state);
	
	Procedural *proc = new Procedural();
	state->addComponent(proc);
	
	game.start(argc, argv);
}