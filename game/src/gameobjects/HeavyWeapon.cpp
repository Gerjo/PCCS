#include "HeavyWeapon.h"
#include "HeavyFactory.h"

HeavyWeapon::HeavyWeapon() {
    setType("weapon");
}

HeavyWeapon::~HeavyWeapon() {

}

LightBullet* HeavyWeapon::createBullet() {
    return (LightBullet*) HeavyFactory::create("bullet");
}
