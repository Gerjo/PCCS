#include "HelicopterAttackState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/LightSoldier.h"
#include "../gameobjects/LightHelicopter.h"

HelicopterAttackState::HelicopterAttackState(LightHelicopter *Helicopter) {
    this->helicopter = Helicopter;
    this->tree = nullptr;
}

void HelicopterAttackState::handle(const phantom::PhantomTime &time) {
    vector<GameObject*> soldiers = ArtificialIntelligence::soldiers;
    if(tree == nullptr) {
        tree = helicopter->findAnsestor<BSPTree>();
    }
    else {
        for(GameObject *soldier : soldiers) {
            float length = (helicopter->getPosition() - soldier->getPosition()).getLengthSq();
            if(tree->inlineOfSight(helicopter, soldier)) {
                if(!helicopter->isAttacking()) {
                    if(helicopter->getVictim() == soldier || !helicopter->hasVictim()) {     
                        if(length > 30000)
                            helicopter->fly(soldier->getPosition());
                        helicopter->attack(soldier);
                        break;
                    }
                }
            }
            if(length >= 160000) {
                helicopter->stopShooting();
                //ai->setActive<HelicopterIdleState>();
            }
        }
    }
}