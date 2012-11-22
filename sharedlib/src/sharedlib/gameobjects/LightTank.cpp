#include "LightTank.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/AIIdleState.h"
#include "../artificialintelligence/AIAttackState.h"

LightTank::LightTank() {
    setType("Tank");

    _boundingBox.size.x = 120.0f;
    _boundingBox.size.y = 120.0f;

    idleState = new AIIdleState();
    attackState = new AIAttackState();

    addComponent(new ArtificialIntelligence(this, idleState, attackState));

    setHealth(2000.0f);
}

LightTank::~LightTank() {
    delete idleState;
    delete attackState;
}

void LightTank::attack(GameObject *victim) {
}

void LightTank::update(const Time& time) {
    GameObject::update(time);
}