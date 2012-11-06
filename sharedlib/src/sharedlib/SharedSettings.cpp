#include "SharedSettings.h"

double SharedSettings::PING_INTERVAL() {
    return 7.0;
}

float SharedSettings::BSP_WIDTH(){
    return 20000.0f;
}
float SharedSettings::BSP_HEIGHT(){
    return 20000.0f;
}
float SharedSettings::BSP_SMALLESTSIZE(){
    return 20.0f;
}
unsigned SharedSettings::BSP_MAXCOLLISIONSPERSPACE(){
    return 20;
}

void SharedSettings::load(void){
}