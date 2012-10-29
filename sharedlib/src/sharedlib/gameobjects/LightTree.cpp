#include "LightTree.h"

LightTree::LightTree() : GameObject() {
    setType("Tree");

    _boundingBox.size.x = 106;
    _boundingBox.size.y = 100;
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