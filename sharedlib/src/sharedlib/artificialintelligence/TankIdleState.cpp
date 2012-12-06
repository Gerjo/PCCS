#include "TankIdleState.h"
#include "ArtificialIntelligence.h"
#include "TankAttackState.h"
#include "../gameobjects/LightSoldier.h"
#include "../gameobjects/LightTank.h"

TankIdleState::TankIdleState(LightTank *tank) {
    this->tank = tank;
}

void TankIdleState::handle(const phantom::PhantomTime& time) {
    vector<GameObject*> soldiers = ArtificialIntelligence::soldiers;
    for(GameObject *soldier : soldiers) {
        if((tank->getPosition() - soldier->getPosition()).getLengthSq() < 160000) {
            if(ai->setActive<TankAttackState>() != nullptr) {
                ai->setNonActive<TankIdleState>();
                return;
            }
        }
    }
}