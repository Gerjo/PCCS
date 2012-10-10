#include "GameObject.h"
#include "../tiles/Tile.h"

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