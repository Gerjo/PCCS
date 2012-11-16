#include "ISettings.h"

bool ISettings::loadFromFile(string filename) {
    return true;
}

string ISettings::getRandomNickname() {
    // A unique name, great if you run multiple clients.
    stringstream ss;
    ss << "default-" << std::fixed << phantom::Util::getTime();
   return ss.str();
}