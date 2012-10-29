#include "Settings.h"

double Settings::AUTH_GRACE_TIME   = 2.0;
double Settings::PING_GRACE_TIME   = 10.0;
string Settings::LISTEN_PORT       = "8075";
bool Settings::BROADCAST_SELF_ECHO = false;

static float Settings::BSP_WIDTH                    = 2000.0f;
static float Settings::BSP_HEIGHT                   = 2000.0f;
static float Settings::BSP_SMALLESTSIZE             = 20.0f;
static unsigned Settings::BSP_MAXCOLLISIONSPERSPACE = 50;

void Settings::load(void) {
    // load from a file?
}