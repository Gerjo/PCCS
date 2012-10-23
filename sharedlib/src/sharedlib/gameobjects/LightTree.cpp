#include "LightTree.h"

LightTree::LightTree() : GameObject() {
    setType("Tree");

    _boundingBox.size.x = 32;
    _boundingBox.size.y = 32;
}

bool LightTree::canCollideWith(Composite* other) {
    if(other->isType("Tree")) {
        return false;
    }

    return true;
}