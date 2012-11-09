#include "AssaultRifle.h"
#include "AbstractBehaviour.h"
AssaultRifle::AssaultRifle(){
    _rateOfFire = 1000;
    _range = 1000.0f;
    _cooldownTimeSeconds = 1.0f;
    _lastShootTime = 0.0;
    _typeName = "AssaultRifle";
}

void AssaultRifle::render(phantom::Graphics* g){

}