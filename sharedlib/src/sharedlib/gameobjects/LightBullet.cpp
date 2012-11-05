#include "LightBullet.h"

#include "behaviours/StandardBullet.h"

LightBullet::LightBullet() :
    _velocity(500, 500, 0),
    _direction(1, 1, 0),
    _ttl(1),
    _damage(50.0f),
    owner(0) {

        setType("Bullet");
        _boundingBox.size.x = 10;
        _boundingBox.size.y = 10;
        _creationTime       = phantom::Util::getTime();
        _bulletBehaviour = nullptr;
        setBehaviour(new StandardBullet());

}

LightBullet::~LightBullet() {
    delete _bulletBehaviour;
    _bulletBehaviour = 0;
}

void LightBullet::setBehaviour(BulletBehaviour* newBehaviour){
    delete _bulletBehaviour;

    _bulletBehaviour = newBehaviour;
}

void LightBullet::fromData(Data& data) {
    GameObject::fromData(data);
    _creationTime = data("creationtime");
    _direction.x  = data("d-x");
    _direction.y  = data("d-y");
    _direction.z  = data("d-z");

    // strategy = StrategyFactory::create(data("strategy"));
}

void LightBullet::toData(Data& data) {
    GameObject::toData(data);
    data("creationtime") = static_cast<float>(_creationTime);
    data("d-x")          = _direction.x;
    data("d-y")          = _direction.y;
    data("d-z")          = _direction.z;

    //data("strategy") = StrategyFactory::reverseLookup(strategy);
}

void LightBullet::setDirection(Vector3& direction) {
    //_direction = direction;
    _direction = _bulletBehaviour->setDirection(direction);
}

void LightBullet::update(const Time& time) {
    GameObject::update(time);

    _position += _velocity * _direction * time.getElapsed();

    _ttl -= time.getElapsed();

    if(_ttl < 0) {
        destroy();
    }
}

void LightBullet::onCollision(Composite* entity) {
    //_bulletBehaviour->onCollision(entity);
    if(entity->isType(getType()) || entity->isType("Soldier") || entity->isType("Crate")) {
        return;
    }

    // Studies have shown that shooting your own weapon, is not a great idea.
    if(entity->isType("Weapon")) {
        return;
    }

    if(owner != 0) {
        owner->onKillSomething(static_cast<GameObject*>(entity));
    }

    destroy();
    static_cast<Entity*>(entity)->removeHealth(_damage);
}