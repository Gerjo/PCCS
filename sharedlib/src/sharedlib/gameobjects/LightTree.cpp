#include "LightTree.h"

LightTree::LightTree() : GameObject() {
    setType("Tree");
    isStatic = true;
    _boundingBox.size.x = 80;
    _boundingBox.size.y = 80;
    setHealth(400.0f);

    // Determine who cannot walk over this object:
    solidState |= SolidStateBits::PLAYER;
}
