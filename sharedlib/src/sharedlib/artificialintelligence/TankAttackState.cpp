#include "TankAttackState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/LightSoldier.h"
#include "../gameobjects/LightTank.h"

TankAttackState::TankAttackState(LightTank *tank) {
    this->tank = tank;
    this->tree = nullptr;
}

void TankAttackState::construct() {
}

void TankAttackState::handle(const phantom::PhantomTime &time) {
    vector<GameObject*> iteratorsincompatiblewtf = ArtificialIntelligence::soldiers;
    if(tree == nullptr) {
        tree = tank->findAnsestor<BSPTree>();
    }
    else {
        for(GameObject *soldier : iteratorsincompatiblewtf) {
            if(tree->inlineOfSight(tank, soldier)) {
                tank->drive(soldier->getPosition());
                if(!tank->isAttacking) {

                    tank->attack(soldier);
                    break;
                }
            } else {
                if(tank->isAttacking)
                    tank->stopShooting();
            }
        }
    }
}

void TankAttackState::destruct() {
}