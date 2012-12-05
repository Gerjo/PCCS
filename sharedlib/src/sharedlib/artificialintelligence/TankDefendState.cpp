#include "ArtificialIntelligence.h"
#include "../pathfinding/BSPTree.h"
#include "../gameobjects/LightTank.h"
#include "TankDefendState.h"

TankDefendState::TankDefendState(LightTank *tank) {
    this->tank = tank;
}

void TankDefendState::handle(const phantom::PhantomTime& time) {
    vector<GameObject*> iteratorsincompatiblewtf = ArtificialIntelligence::soldiers;
    if(tree == nullptr) {
        tree = tank->findAnsestor<BSPTree>();
    }
    else {
        for(GameObject *soldier : iteratorsincompatiblewtf) {
            float length = (tank->getPosition() - soldier->getPosition()).getLengthSq();
            if(tree->inlineOfSight(tank, soldier)) {
                if(!tank->isAttacking) {
                    if(tank->getVictim() == soldier || !tank->hasVictim()) {
                        tank->attack(soldier);
                        break;
                    }
                }
                return;
            }
            if(length >= 160000) {
                tank->stopShooting();
            }
        }
    }
}