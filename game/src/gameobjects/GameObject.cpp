#include "GameObject.h"
#include "../tiles/Tile.h"

GameObject::GameObject() : _canHover(false) {
}

void GameObject::onMouseHover(void) {
    // To be overridden.
}

bool GameObject::canHover(void) {
    return _canHover;
}
