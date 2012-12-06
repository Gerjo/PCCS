#include "HelicopterAttackState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/LightSoldier.h"
#include "../gameobjects/LightHelicopter.h"
#include "../services/Services.h"

HelicopterAttackState::HelicopterAttackState(LightHelicopter *Helicopter) {
    this->helicopter = Helicopter;
    this->tree = nullptr;
}

void HelicopterAttackState::handle(const phantom::PhantomTime &time) {
    vector<GameObject*> soldiers = ArtificialIntelligence::soldiers;
    for(GameObject *soldier : soldiers) {
        float length = (helicopter->getPosition() - soldier->getPosition()).getLengthSq();
        if(length < Services::settings()->helicopter_detection_range) {
            if(!helicopter->isAttacking()) {
                if(helicopter->getVictim() == soldier || !helicopter->hasVictim()) {     
                    if(length > Services::settings()->helicopter_start_flying_range)
                        helicopter->fly(soldier->getPosition());
                    //helicopter->attack(soldier);
                    break;
                }
            }
        }
        if(length >= Services::settings()->helicopter_detection_range) {
            if(helicopter->isAttacking())
                helicopter->stopShooting();
        }
    }
}