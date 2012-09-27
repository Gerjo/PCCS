#include <iostream>

#include "Game.h"

using namespace std;

#include <phantom.h>
#include <graphics/GLUTRenderer.h>
#include <input/GLUTInputState.h>
#include <graphics/GLUTDriver.h>
#include <graphics/BaseDriver.h>

#include "Game.h"

int main(int argc, char *argv[]) {

    Game game("   _____ _____ _____ _____  "
              "  |  _  |     |     |   __| "
              "  |   __|   --|   --|__   | "
              "  |__|  |_____|_____|_____| "
              "                            ");

    GLUTDriver baseDriver;

    game.start(argc, argv, &baseDriver);


    return 0;
}