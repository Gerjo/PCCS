#include "UID.h"

unsigned long long UID::offset = 0;

string UID::generate() {
    stringstream ss;

    ss << "UID" << offset++;

    return ss.str();
}