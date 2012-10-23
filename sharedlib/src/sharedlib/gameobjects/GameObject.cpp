#include "GameObject.h"

GameObject::GameObject() : _canHover(false) {

}

void GameObject::onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen) {
    // To be overridden.
}

bool GameObject::canHover(void) {
    return _canHover;
}

void GameObject::onSelect() {

}

void GameObject::onDeselect() {

}

float GameObject::distanceTo(GameObject* gob) {
    return _position.distanceTo(gob->_position);
}

float GameObject::distanceToSq(GameObject* gob) {
    return _position.distanceToSq(gob->_position);
}

Vector3 GameObject::directionTo(GameObject* gob) {
    Vector3 direction = gob->_position - _position;
    direction.normalize();
    return direction;
}

void GameObject::paint(void) {
    // Your painting code here.
}

void GameObject::repaint(void) {
    paint(); // TODO: chain multiple calls till vblank?
}
