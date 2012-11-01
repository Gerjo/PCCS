#include "LightTree.h"

LightTree::LightTree() : GameObject() {
    setType("Tree");
    isStatic = true;
    _boundingBox.size.x = 64;
    _boundingBox.size.y = 64;
}

bool LightTree::canCollideWith(Composite* other) {
    if(other->isType("Tree")) {
        return false;
    }

    return true;
}

void LightTree::fromData(Data& data) {
    GameObject::fromData(data);
}

void LightTree::toData(Data& data) {
    GameObject::toData(data);
}