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

void LightTree::fromData(Data& data) {
    _boundingBox.size.x = data("width");
    _boundingBox.size.y = data("height");
    _position.x = data("x");
    _position.y = data("y");
}

void LightTree::toData(Data& data) {
    data("width")  = _boundingBox.size.x;
    data("height") = _boundingBox.size.y;

    data("x") = _position.x;
    data("y") = _position.y;
}