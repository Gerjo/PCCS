#include "TankIdleState.h"
#include "ArtificialIntelligence.h"
#include "TankAttackState.h"
#include "../gameobjects/LightSoldier.h"
#include "../gameobjects/LightTank.h"

TankIdleState::TankIdleState(LightTank *tank) {
    this->tank = tank;
}

void TankIdleState::construct() {
}

void TankIdleState::handle(const phantom::PhantomTime& time) {
    vector<GameObject*> iteratorsincompatiblewtf = ArtificialIntelligence::soldiers;
    for(GameObject *soldier : iteratorsincompatiblewtf) {
        if((tank->getPosition() - soldier->getPosition()).getLengthSq() < pow(400, 2)) {
            if(!ai->setActive<TankAttackState>())
                if(!ai->setActive<TankIdleState>())
                    return;
        } else {
        }
    }
}

void TankIdleState::destruct() {
}