#ifdef WIN32
#   ifdef _DEBUG
#       define _CRTDBG_MAP_ALLOC
#       define _CRTDBG_MAP_ALLOC_NEW
#       include <stdlib.h>
#       include <crtdbg.h>
#   endif /* Debug */
#endif /* win32*/

#include <phantom.h>
#include <glut/GLUTDriver.h>
#include <yaxl.h>
#include <sharedlib/sharedlib.h>

#include "ProceduralDemo.h"

using namespace phantom;

int main(int argc, char* argv[]){
#ifdef WIN32
#ifdef _DEBUG
    _CrtSetBreakAlloc(3126);
#endif
#endif

    PhantomGame* game = new PhantomGame("");

    game->setDriver(new GLUTDriver(game));
    ProceduralDemo* demo = new ProceduralDemo();
    game->pushGameState(demo);
    game->start(argc, argv);
    delete demo;
    delete game;

#ifdef WIN32
#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif
#endif


    return 0;
}

