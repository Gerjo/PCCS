#include "LightWeapon.h"
#include "LightFactory.h"

#include "behaviours/AssaultRifle.h"

LightWeapon::LightWeapon() : _range(600), _lastShootTime(0), _cooldownTimeSeconds(1.0f) {
    setType("Weapon");
    _weaponBehaviour = nullptr;
    setWeaponBehaviour(new AssaultRifle());
}

LightWeapon::~LightWeapon() {
    delete _weaponBehaviour;
    _weaponBehaviour = 0;
}

LightBullet* LightWeapon::createBullet() {
    startCooldown();
    return (LightBullet*) LightFactory::create("bullet");
}

void LightWeapon::setWeaponBehaviour(WeaponBehaviour* newBehaviour){
    delete _weaponBehaviour;

    _weaponBehaviour = newBehaviour;
}

float LightWeapon::getRange(void) {
    return _weaponBehaviour->getRange();
}

float LightWeapon::getRangeSq(void) {
    return _weaponBehaviour->getRangeSq();
}

bool LightWeapon::isCooldownExpired(void) {
    return _weaponBehaviour->isCoolDownExpired();
}

void LightWeapon::startCooldown(void) {
    _weaponBehaviour->startCoolDown();
}