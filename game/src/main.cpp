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
    Game game("   _____ _____ _____ _____   "
              "  |  _  |     |     |   __|  "
              "  |   __|  ===|  ===|__   |  "
              "  |__|  |_____|_____|_____|  "
              "                             ");

    game.start(argc, argv);

    return 0;
}
