#include "LightBullet.h"

LightBullet::LightBullet() :
        _velocity(20, 20, 0),
        _direction(1, 1, 0),
        _ttl(1) {

    setType("Bullet");
    _boundingBox.size.x = 10;
    _boundingBox.size.y = 10;
    _creationTime       = phantom::Util::getTime();

}

LightBullet::~LightBullet() {

}

void LightBullet::setBehaviour(BulletBehaviour* newBehaviour){
    if(_bulletBehaviour != nullptr)
        delete _bulletBehaviour;
    _bulletBehaviour = newBehaviour;
}

void LightBullet::setDirection(Vector3& direction) {
    _direction = direction;
    //_bulletBehaviour->setDirection(direction);
}

void LightBullet::update(const Time& time) {
    GameObject::update(time);

    _position += _velocity * _direction;

    if(time.getTime() - _creationTime > _ttl) {
        destroy();
    }
}

void LightBullet::onCollision(Composite* entity) {
    //_bulletBehaviour->onCollision(entity);
    if(entity->isType(getType()) || entity->isType("Soldier")) {
        return;
    }

    // Studies have shown that shooting your own weapon, is not a great idea.
    if(entity->isType("Weapon")) {
        return;
    }

    owner->onKillSomething(static_cast<GameObject*>(entity));

    destroy();
    entity->destroy();
}