#include "Bullet.h"

Bullet::Bullet(Entity* owner) :
    _velocity(10, 10, 0),
    _direction(1, 1, 0),
    _ttl(1)
{
    setType("Bullet");
    _boundingBox.size.x = 10;
    _boundingBox.size.y = 10;
    _position     = owner->getPosition();
    _creationTime = phantom::Util::getTime();

    draw();
}

Bullet::~Bullet() {

}

void Bullet::setDirection(Vector3& direction) {
    _direction = direction;
}

void Bullet::update(const float& elapsed) {
    GameObject::update(elapsed);

    _position += _velocity * _direction;

    //getGraphics().rotate(45);

    if(phantom::Util::getTime() - _creationTime > _ttl) {
        // remove from parent.
    }
}

void Bullet::onCollision(Composite* entity) {
    if(entity->isType(getType()) || entity->isType("Soldier")) {
        return;
    }

    stringstream ss;
    ss << "Bullet impacts a " << entity->getType();

    //_velocity = Vector3();
    Console::log(ss.str());
    destroy();
    entity->destroy();
}

void Bullet::draw(void) {
    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::WHITE)
            .rect(0, 0, _boundingBox.size.x, _boundingBox.size.y)
            .stroke()
            ;
}
