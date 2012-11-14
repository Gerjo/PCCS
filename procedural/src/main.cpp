#include <phantom.h>
#include <glut/GLUTDriver.h>
#include <yaxl.h>
#include <sharedlib/sharedlib.h>

using namespace phantom;

int main(int argc, char* argv[])
{
    PhantomGame game("conf/phantomconfig.cfg");
    game.setDriver(new GLUTDriver(&game));

    game.start(argc, argv);

	return 0;
}

