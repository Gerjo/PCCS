#include "LightWeapon.h"
#include "LightFactory.h"

LightWeapon::LightWeapon() {
    setType("weapon");
}

LightWeapon::~LightWeapon() {

}

LightBullet* LightWeapon::createBullet() {
    return (LightBullet*) LightFactory::create("bullet");
}
