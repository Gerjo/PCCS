#include "core/GameHub.h"

#include <sharedlib/networking/networking.h>
#include <sharedlib/serialization/Data.h>
#include <sharedlib/testsuite/TestSuite.h>
#include <yaxl.h>
#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    {TestSuite testsuite;}

    GameHub server;
    return 0;
}
