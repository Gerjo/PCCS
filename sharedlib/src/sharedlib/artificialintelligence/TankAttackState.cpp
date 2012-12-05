#include "TankAttackState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/LightSoldier.h"
#include "../gameobjects/LightTank.h"

TankAttackState::TankAttackState(LightTank *tank) {
    this->tank = tank;
    this->tree = nullptr;
}

void TankAttackState::handle(const phantom::PhantomTime &time) {
    vector<GameObject*> soldiers = ArtificialIntelligence::soldiers;
    if(tree == nullptr) {
        tree = tank->findAnsestor<BSPTree>();
    }
    else {
        for(GameObject *soldier : soldiers) {
            float length = (tank->getPosition() - soldier->getPosition()).getLengthSq();
            if(tree->inlineOfSight(tank, soldier)) {
                if(!tank->isAttacking) {
                    if(tank->getVictim() == soldier || !tank->hasVictim()) {     
                        if(length > 30000)
                            tank->drive(soldier->getPosition());
                        tank->attack(soldier);
                        break;
                    }
                }
            }
            if(length >= 160000) {
                tank->stopShooting();
                ai->setActive<TankIdleState>();
            }
        }
    }
}