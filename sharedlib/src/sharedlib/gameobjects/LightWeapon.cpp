#include "LightWeapon.h"
#include "LightFactory.h"

#include "AssaultRifle.h"

LightWeapon::LightWeapon() : _range(600), _lastShootTime(0), _cooldownTimeSeconds(0.1f) {
    setType("Weapon");

    // Probably should go somewhere else!
    _weaponBehavour = new AssaultRifle();
}

LightWeapon::~LightWeapon() {
}

LightBullet* LightWeapon::createBullet() {
    startCooldown();
    return (LightBullet*) LightFactory::create("bullet");
}

float LightWeapon::getRange(void) {
    return _weaponBehavour->getRange();
}

float LightWeapon::getRangeSq(void) {
    return _weaponBehavour->getRangeSq();
}

bool LightWeapon::isCooldownExpired(void) {
    return _weaponBehavour->isCoolDownExpired();
}

void LightWeapon::startCooldown(void) {
    _weaponBehavour->startCoolDown();
}