#include "LightTank.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/TankIdleState.h"
#include "../artificialintelligence/TankAttackState.h"

LightTank::LightTank() {
    setType("Tank");

    _boundingBox.size.x = 120.0f;
    _boundingBox.size.y = 120.0f;

    idleState = new TankIdleState();
    attackState = new TankAttackState(this);

    addComponent(new ArtificialIntelligence(this, idleState, attackState));

    setHealth(2000.0f);
}

LightTank::~LightTank() {
    delete idleState;
    delete attackState;
}

void LightTank::attack(GameObject *victim) {
    Box3& boundingbox = victim->getBoundingBox();

    _victim = victim;
    _victim->registerDestoryEvent(this);
}

void LightTank::update(const Time& time) {
    GameObject::update(time);
}