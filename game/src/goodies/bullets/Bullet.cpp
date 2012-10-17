#include "Bullet.h"

Bullet::Bullet(Entity* owner) :
    _velocity(1, 1, 0),
    _direction(1, 1, 0)
{
    _position = owner->getPosition();

    draw();
}

Bullet::~Bullet() {

}

void Bullet::setDirection(Vector3& direction) {
    _direction = direction;
}

void Bullet::update(const float& elapsed) {
    Entity::update(elapsed);

    Vector3 add = _velocity * _direction;

    _position += add;
}

void Bullet::draw(void) {
    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::WHITE)
            .rect(0, 0, 10, 10)
            .stroke()
            ;
}
