#include "AssaultRifle.h"

AssaultRifle::AssaultRifle(){
    _rateOfFire = 1000;
    _range = 1000.0f;
    _cooldownTimeSeconds = 0.1f;
    _lastShootTime = 0.0;
}

void AssaultRifle::render(){

}