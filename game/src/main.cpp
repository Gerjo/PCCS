#include <iostream>

#include "Game.h"

using namespace std;

#include <phantom.h>
#include <glut/GLUTRenderer.h>
#include <glut/GLUTInputState.h>
#include <glut/GLUTDriver.h>
#include <core/Driver.h>

#include "Game.h"

int main(int argc, char *argv[]) {
    cout <<   "   _____ _____ _____ _____  " << endl <<
              "  |  _  |     |     |   __| " << endl <<
              "  |   __|  ===|  ===|__   | " << endl <<
              "  |__|  |_____|_____|_____| " << endl <<
              "                            " << endl;
    Game game("   _____ _____ _____ _____   "
              "  |  _  |     |     |   __|  "
              "  |   __|  ===|  ===|__   |  "
              "  |__|  |_____|_____|_____|  "
              "                             ");

    GLUTDriver baseDriver;

    game.start(argc, argv, &baseDriver);

    return 0;
}
