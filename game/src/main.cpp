#ifdef WIN32
#   ifdef _DEBUG
#       define _CRTDBG_MAP_ALLOC
#       define _CRTDBG_MAP_ALLOC_NEW
#       include <stdlib.h>
#       include <crtdbg.h>
#   endif /* Debug */
#endif /* win32*/

#include <iostream>
#include "Game.h"

using namespace std;

#include <phantom.h>

int main(int argc, char *argv[]) {
#ifdef WIN32
#ifdef _DEBUG
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
    _CrtSetBreakAlloc(-1);
#endif
#endif

    cout << "   _____ _____ _____ _____   " << endl <<
            "  |  _  |     |     |   __|  " << endl <<
            "  |   __|  ===|  ===|__   |  " << endl <<
            "  |__|  |_____|_____|_____|  " << endl <<
            "                             " << endl;

    Game *game = new Game("conf/phantomconfig.cfg");

    game->start(argc, argv);

    delete game;

    /*
    real	0m13.817s
    user	0m23.114s
    sys	0m2.227s
    */

    return 0;
}
