#include "LightBullet.h"
#include "LightSoldier.h"

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

void LightBullet::fromData(Data& data) {
    GameObject::fromData(data);
    _creationTime = data("creationtime");
    _direction.x  = data("d-z");
    _direction.y  = data("d-z");
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
    _direction = direction;
}

void LightBullet::update(const Time& time) {
    GameObject::update(time);

    _position += _velocity * _direction;

    if(time.getTime() - _creationTime > _ttl) {
        destroy();
    }
}

void LightBullet::onCollision(Composite* entity) {

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