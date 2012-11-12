#include "LightTank.h"

LightTank::LightTank() {
    setType("Tank");

    _boundingBox.size.x = 120.0f;
    _boundingBox.size.y = 120.0f;

    setHealth(2000.0f);
}

LightTank::~LightTank() {
}

void LightTank::attack(GameObject *victim) {
}

void LightTank::update(const Time& time) {
    GameObject::update(time);
}