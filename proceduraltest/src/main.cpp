#include <phantom.h>
#include <opengl/GLDriver.h>
#include <Procedural.h>

using namespace phantom;

int main(int argc, char *argv[]) {
	PhantomGame game("");
	game.setDriver(new GLDriver(&game));
    game.getDriver()->enableCamera(game.getDriver()->createCamera());
	GameState *state = new GameState();
    game.pushGameState(state);
    //game.addComponent(state);

	Procedural *proc = new Procedural();
	game.addComponent(proc);
    proc->generateWorld(1920,1080,8,1000);
    proc->generatePaths(8);
    proc->paint();
    proc->paintPath();

	game.start(argc, argv);

    delete state;
    return 0;
}