#include "SharedSettings.h"

double SharedSettings::PING_INTERVAL = 7.0; // seconds!

float SharedSettings::BSP_WIDTH(){
    return 4000.0f;
}
float SharedSettings::BSP_HEIGHT(){
    return 4000.0f;
}
float SharedSettings::BSP_SMALLESTSIZE(){
    return 20.0f;
}
unsigned SharedSettings::BSP_MAXCOLLISIONSPERSPACE(){
    return 50;
}

void SharedSettings::load(void){
}