#include "LightTank.h"

LightTank::LightTank() {
    setType("tank");

    _boundingBox.size.x = 120.0f;
    _boundingBox.size.y = 120.0f;
}

LightTank::~LightTank() {
}

void LightTank::attack(GameObject *victim) {
}

void LightTank::update(const Time& time) {
    GameObject::update(time);
}