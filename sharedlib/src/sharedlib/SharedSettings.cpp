#include "SharedSettings.h"

double SharedSettings::PING_INTERVAL() {
    return 7.0;
}

double SharedSettings::PING_INTERVALMASTER() {
    return 1.0;
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

std::string SharedSettings::MASTER_HOST() {
    return "localhost";
}

std::string SharedSettings::MASTER_PORT() {
    return "8071";
}

void SharedSettings::load(void){
}