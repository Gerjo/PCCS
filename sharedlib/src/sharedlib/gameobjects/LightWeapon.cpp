#include "LightWeapon.h"
#include "LightFactory.h"

#include <cstdio>

LightWeapon::LightWeapon() : _range(600), _lastShootTime(0), _cooldownTimeSeconds(0.1f) {
    setType("Weapon");
}

LightWeapon::~LightWeapon() {

}

LightBullet* LightWeapon::createBullet() {
    startCooldown();
    return (LightBullet*) LightFactory::create("bullet");
}

float LightWeapon::getRange(void) {
    return _range;
}

float LightWeapon::getRangeSq(void) {
    return _range * _range;
}

bool LightWeapon::isCooldownExpired(void) {
    const double now = phantom::Util::getTime();

    return now - _lastShootTime > _cooldownTimeSeconds;
}

void LightWeapon::startCooldown(void) {
    _lastShootTime = phantom::Util::getTime();
}