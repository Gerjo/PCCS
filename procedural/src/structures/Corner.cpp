#include "Corner.h"

namespace PGC{
    Corner::Corner(): adjacent(0), touches(0), protrudes(0){
        isBorder = false;
        index = 0;
    }
    Corner::~Corner(){
        delete point;
    }
}