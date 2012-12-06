#include "HelicopterAttackState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/LightSoldier.h"
#include "../gameobjects/LightHelicopter.h"

HelicopterAttackState::HelicopterAttackState(LightHelicopter *Helicopter) {
    this->Helicopter = Helicopter;
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
            if(tree->inlineOfSight(Helicopter, soldier)) {
                if(!Helicopter->isAttacking) {
                    if(Helicopter->getVictim() == soldier || !Helicopter->hasVictim()) {     
                        if(length > 30000)
                            Helicopter->drive(soldier->getPosition());
                        Helicopter->attack(soldier);
                        break;
                    }
                }
            }
            if(length >= 160000) {
                Helicopter->stopShooting();
                //ai->setActive<HelicopterIdleState>();
            }
        }
    }
}