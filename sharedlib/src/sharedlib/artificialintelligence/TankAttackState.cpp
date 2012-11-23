#include "TankAttackState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/LightSoldier.h"

TankAttackState::TankAttackState(LightTank *tank) {
    this->tank = tank;
}

void TankAttackState::construct() {
}

void TankAttackState::handle(const phantom::Time &time) {
    for(GameObject *soldier : ArtificialIntelligence::soldiers) {
        if((tank->getPosition() - soldier->getPosition()).getLengthSq() < pow(200, 2)) {
            tank->drive(soldier->getPosition());
            if(!tank->isAttacking) {
                tank->attack(soldier);
            }
        } else {
            if(tank->isAttacking)
                tank->stopShooting();
        }
    }
}

void TankAttackState::destruct() {
}