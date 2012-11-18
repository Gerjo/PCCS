#include "HeavyBullet.h"
#include <utils/Maths.h>

HeavyBullet::HeavyBullet() {

}

HeavyBullet::~HeavyBullet() {

}

void HeavyBullet::update(const Time& time) {
    LightBullet::update(time);

    _bulletBehaviour->render(&getGraphics());
}

void HeavyBullet::onCollision(Composite* entity) {

    // Objects we can shoot through:
    if(entity->isType(getType())        ||
            entity->isType("Weapon")    ||
            entity->isType("Soldier")   ||
            entity->isType("Crate")) {
        return;
    }

    // We've reached this point, destroy the bullet:
    destroy();

    // Invincible objects:
    if(entity->isType("Tree")) {
        return;
    }

    // We've reached this point, so let's deal some damage: NB: Some bullets
    // are "animation" only, so they need not do damage and network sync.
    if(_hasAuthority) {
        Data data;
        data("damage") = _damage;

        Dedicated* network = getGame<Game*>()->dedicated;
        Message<Data>* message = new Message<Data>("take-damage", data);

        // Let the server know about our intent to damage a tree. It's up to
        // the server to remove health.
        Services::broadcast((GameObject*)entity, message);
    }
}