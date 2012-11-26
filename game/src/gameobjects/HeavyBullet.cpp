#include "HeavyBullet.h"
#include <utils/Maths.h>

HeavyBullet::HeavyBullet() {

}

HeavyBullet::~HeavyBullet() {

}

void HeavyBullet::update(const PhantomTime& time) {
    LightBullet::update(time);

    _bulletBehaviour->render(&getGraphics());
}

void HeavyBullet::killList(vector<string> killList) {
    _killList = killList;
}

void HeavyBullet::onCollision(Composite* entity) {
    if(entity->isType(getType()))
        return;
    if(entity->isType("Weapon"))
        return;
    if(find(_killList.begin(), _killList.end(), string(entity->getType())) == _killList.end())
        return;

    // We've reached this point, destroy the bullet:
    destroy();

    // Invincible objects:
    // *COUGH* a tree is stronger than a tank? :D
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