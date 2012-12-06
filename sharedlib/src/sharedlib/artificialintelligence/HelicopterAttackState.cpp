#include "HelicopterAttackState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/LightSoldier.h"
#include "../gameobjects/LightHelicopter.h"

float HelicopterAttackState::maxdist = 200000.0f;
float HelicopterAttackState::startflying = 30000.0f;

HelicopterAttackState::HelicopterAttackState(LightHelicopter *Helicopter) {
    this->helicopter = Helicopter;
    this->tree = nullptr;
}

void HelicopterAttackState::handle(const phantom::PhantomTime &time) {
    vector<GameObject*> soldiers = ArtificialIntelligence::soldiers;
    for(GameObject *soldier : soldiers) {
        float length = (helicopter->getPosition() - soldier->getPosition()).getLengthSq();
        if(length < maxdist) {
            if(!helicopter->isAttacking()) {
                if(helicopter->getVictim() == soldier || !helicopter->hasVictim()) {     
                    if(length > 30000)
                        helicopter->fly(soldier->getPosition());
                    //helicopter->attack(soldier);
                    break;
                }
            }
        }
        if(length >= maxdist) {
            if(helicopter->isAttacking())
                helicopter->stopShooting();
        }
    }
}