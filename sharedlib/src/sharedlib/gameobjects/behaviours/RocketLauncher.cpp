#include "RocketLauncher.h"

RocketLauncher::RocketLauncher(){
    _rateOfFire = 200;
    _range = 5000.0f;
    _lastShootTime = 0.0f;
    _typeName = "RocketLauncher";
}

void RocketLauncher::render(phantom::Graphics* g){

}