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
        if((tank->getPosition() - soldier->getPosition()).getLengthSq() < 1000.0f) {
            tank->attack(soldier);
        }
    }
}

void TankAttackState::destruct() {
}