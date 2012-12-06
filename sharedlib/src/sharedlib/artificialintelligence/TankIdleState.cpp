#include "TankIdleState.h"
#include "ArtificialIntelligence.h"
#include "TankAttackState.h"
#include "../gameobjects/LightSoldier.h"
#include "../gameobjects/LightTank.h"
#include "../services/Services.h"

TankIdleState::TankIdleState(LightTank *tank) {
    this->tank = tank;
}

void TankIdleState::handle(const phantom::PhantomTime& time) {
    vector<GameObject*> soldiers = ArtificialIntelligence::soldiers;
    for(GameObject *soldier : soldiers) {
        if((tank->getPosition() - soldier->getPosition()).getLengthSq() < Services::settings()->tank_detection_range) {
            if(ai->setActive<TankAttackState>() != nullptr) {
                ai->setNonActive<TankIdleState>();
                return;
            }
        }
    }
}