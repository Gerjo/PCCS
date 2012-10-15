#include "Weapon.h"

Weapon::Weapon() :
    _name("Generic Gun"),
    _range(100)
{

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