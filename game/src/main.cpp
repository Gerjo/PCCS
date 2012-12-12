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
#include <sharedlib/testsuite/TestSuite.h>
#include <phantom.h>

int main(int argc, char *argv[]) {
#ifdef WIN32
#ifdef _DEBUG
    _CrtMemState memstateBegin, memstateEnd, memstateDiff;
    _CrtSetBreakAlloc(-1);
    _CrtMemCheckpoint(&memstateBegin);
#endif
#endif

    {TestSuite testsuite;}

    {
        cout << "   _____ _____ _____ _____   " << endl <<
                "  |  _  |     |     |   __|  " << endl <<
                "  |   __|  ===|  ===|__   |  " << endl <<
                "  |__|  |_____|_____|_____|  " << endl <<
                "                             " << endl;

        Game game("conf/phantomconfig.cfg");

        game.start(argc, argv);
    }

    delete Services::settings();

#ifdef WIN32
#ifdef _DEBUG
    _CrtMemCheckpoint(&memstateEnd);
    if(_CrtMemDifference(&memstateDiff, &memstateBegin, &memstateEnd))
        _CrtMemDumpStatistics(&memstateDiff);

    _CrtDumpMemoryLeaks();
#endif
#endif
    /*
    real	0m13.817s
    user	0m23.114s
    sys	0m2.227s
    */

    return 0;
}
