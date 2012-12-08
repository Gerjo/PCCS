#include "LightObstacle.h"

LightObstacle::LightObstacle() : GameObject() {
    setType("Obstacle");
    isStatic = true;
    _boundingBox.size.x = 90;
    _boundingBox.size.y = 90;
    setHealth(400.0f);

    // Determine who cannot walk over this object:
    solidState |= SolidStateBits::PLAYER;
}
