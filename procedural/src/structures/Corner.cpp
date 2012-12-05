#include "Corner.h"

namespace PGC{
    Corner::Corner(): adjacent(0), touches(0), protrudes(0){
        isBorder = false;
    }
    Corner::~Corner(){
        delete point;
    }
}