#include "HeavyBullet.h"
#include <graphics/particles/Particles.h>
#include <sharedlib/gameobjects/LightEnemy.h>

HeavyBullet::HeavyBullet() {

}

HeavyBullet::~HeavyBullet() {

}

void HeavyBullet::update(const PhantomTime& time) {
    LightBullet::update(time);

    _bulletBehaviour->render(&getGraphics());
}

void HeavyBullet::onCollision(Composite* entity, CollisionData& collisionData) {
    if(entity->isType(getType()) || entity->isType("Weapon"))
        return;

    LightEnemy *enemy = dynamic_cast<LightEnemy*>(entity);
    if(enemy != nullptr) {
        if(find(_killList.begin(), _killList.end(), string(enemy->name())) == _killList.end())
            return;
    }
    else {
        if(find(_killList.begin(), _killList.end(), string(entity->getType())) == _killList.end())
            return;
    }

    getDriver()->getAudio()->playSound("audio/SFX/explosion.ogg", getPosition());

    phantom::Particles *p = new phantom::Particles(2000, "images/particles/fire5.png", Colors::WHITE, 0.2f, 0.5f, 200.0f, Vector3(10.0f, 10.0f, 10.0f), Vector3(0.0f, 0.0f, 0.0f));
    p->setPosition(getPosition());
    getPhantomGame()->addComponent(p);

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