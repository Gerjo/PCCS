#include "Settings.h"

double Settings::AUTH_GRACE_TIME   = 2.0;
double Settings::PING_GRACE_TIME   = 10.0;

bool Settings::BROADCAST_SELF_ECHO = true;

void Settings::load(void) {
    // load from a file?
}