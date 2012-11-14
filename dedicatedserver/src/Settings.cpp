#include "Settings.h"

double Settings::AUTH_GRACE_TIME   = 2.0;
double Settings::PING_GRACE_TIME   = 10.0;
int Settings::LISTEN_PORT          = 8075;
bool Settings::BROADCAST_SELF_ECHO = false;

void Settings::load(void) {
    // load from a file?
}