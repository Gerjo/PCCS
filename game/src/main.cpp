#ifdef WIN32
#   ifdef _DEBUG
#       define _CRTDBG_MAP_ALLOC
#       include <stdlib.h>
#       include <crtdbg.h>
#   endif /* Debug */
#endif /* win32*/

#include <iostream>
#include "Game.h"

using namespace std;

#include <phantom.h>

int main(int argc, char *argv[]) {
    cout <<   "   _____ _____ _____ _____   " << endl <<
              "  |  _  |     |     |   __|  " << endl <<
              "  |   __|  ===|  ===|__   |  " << endl <<
              "  |__|  |_____|_____|_____|  " << endl <<
              "                             " << endl;
    Game *game = new Game("conf/phantomconfig.cfg");

    game->start(argc, argv);

    delete game;

    #ifdef WIN32
    #ifdef _DEBUG
    _CrtDumpMemoryLeaks();
    #endif
    #endif

    return 0;
}
