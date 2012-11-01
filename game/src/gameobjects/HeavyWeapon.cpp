#include "HeavyWeapon.h"
#include "HeavyFactory.h"

HeavyWeapon::HeavyWeapon() {

}

HeavyWeapon::~HeavyWeapon() {

}

LightBullet* HeavyWeapon::createBullet() {
    startCooldown();
    return static_cast<LightBullet*>(HeavyFactory::create("bullet"));
}
