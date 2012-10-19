#include "Weapon.h"

Weapon::Weapon() :
    _name("Generic Gun"),
    _range(100),
    _lastShootTime(0),
    _cooldownTimeSeconds(0.1)
{
    setType("Weapon");
}

string Weapon::getName(void) {
    return _name;
}

float Weapon::getRange(void) {
    return _range;
}

float Weapon::getRangeSq(void) {
    return pow(_range, 2);
}

Bullet* Weapon::createBullet(Entity* owner) {
    startCooldown();

    Bullet* bullet = new Bullet(owner);
    return bullet;
}

bool Weapon::isCooldownExpired(void) {
    const double now = phantom::Util::getTime();

    return now - _lastShootTime > _cooldownTimeSeconds;
}

void Weapon::startCooldown(void) {
    _lastShootTime = phantom::Util::getTime();
}