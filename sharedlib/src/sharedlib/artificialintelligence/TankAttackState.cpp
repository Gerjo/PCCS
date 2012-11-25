#include "TankAttackState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/LightSoldier.h"
#include "../gameobjects/LightTank.h"

TankAttackState::TankAttackState(LightTank *tank) {
    this->tank = tank;
}

void TankAttackState::construct() {
}

void TankAttackState::handle(const phantom::Time &time) {
    vector<GameObject*> iteratorsincompatiblewtf = ArtificialIntelligence::soldiers;
    for(GameObject *soldier : iteratorsincompatiblewtf) {
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