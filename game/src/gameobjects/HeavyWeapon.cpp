#include "HeavyWeapon.h"
#include "HeavyFactory.h"

HeavyWeapon::HeavyWeapon() {

}

HeavyWeapon::~HeavyWeapon() {

}

LightBullet* HeavyWeapon::createBullet() {
    startCooldown();
    return (LightBullet*) HeavyFactory::create("bullet");
}
