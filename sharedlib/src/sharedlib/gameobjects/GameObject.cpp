#include "GameObject.h"

GameObject::GameObject() :
    _canHover(false),
    UID_local(UID::generate())
{

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

void GameObject::fromData(Data& data) {
    UID_network = data("UID_network").toString();
    _position.x = data("x");
    _position.y = data("y");
    _boundingBox.size.x = data("w");
    _boundingBox.size.y = data("h");
}

void GameObject::toData(Data& data) {
    data("UID_network") = UID_network;
    data("UID_local")   = UID_local;
    data("type")        = getType();
    data("x")           = _position.x;
    data("y")           = _position.y;
    data("w")           = _boundingBox.size.x;
    data("h")           = _boundingBox.size.y;
}
