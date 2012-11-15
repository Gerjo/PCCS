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
    //_bulletBehaviour->onCollision(entity);
    if(entity->isType(getType()) || entity->isType("Soldier") || entity->isType("Crate")) {
        return;
    }

    // Studies have shown that shooting your own weapon, is not a great idea.
    if(entity->isType("Weapon")) {
        return;
    }

    destroy();

    // Some bullets are in "animation" only mode, "animated" bullets do no damage.
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