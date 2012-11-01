#include "LightWeapon.h"
#include "LightFactory.h"
#include "behaviours/AssaultRifle.h"
#include <cstdio>

LightWeapon::LightWeapon() : _range(600), _lastShootTime(0), _cooldownTimeSeconds(0.1f) {
    setType("Weapon");
    _weaponBehaviour = nullptr;
    setWeaponBehaviour(new AssaultRifle());
}

LightWeapon::~LightWeapon() {
    if(_weaponBehaviour != nullptr)
        delete _weaponBehaviour;
}

LightBullet* LightWeapon::createBullet() {
    startCooldown();
    return (LightBullet*) LightFactory::create("bullet");
}

void LightWeapon::setWeaponBehaviour(WeaponBehaviour* newBehaviour){
    if(_weaponBehaviour != nullptr)
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