#include "LightWater.h"

LightWater::LightWater() : GameObject() {
    setType("Water");
    isStatic = true;
    _boundingBox.size.x = 90;
    _boundingBox.size.y = 90;
    setHealth(400.0f);

    // Determine who cannot walk over this object:
    solidState |= SolidStateBits::PLAYER;
}
