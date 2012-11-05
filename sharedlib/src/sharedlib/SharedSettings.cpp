#include "SharedSettings.h"

double SharedSettings::PING_INTERVAL() {
    return 7.0;
}
unsigned SharedSettings::UNIQUE_ID(){
    return 20;
}
float SharedSettings::BSP_WIDTH(){
    return 20000.0f;
}
float SharedSettings::BSP_HEIGHT(){
    return 20000.0f;
}
float SharedSettings::BSP_SMALLESTSIZE(){
    return 200.0f;
}
unsigned SharedSettings::BSP_MAXCOLLISIONSPERSPACE(){
    return 20;
}


void SharedSettings::load(void){
}