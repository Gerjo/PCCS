#include "LightTree.h"

LightTree::LightTree() : GameObject() {
    setType("Tree");
    isStatic = true;
    _boundingBox.size.x = 90;
    _boundingBox.size.y = 90;
    setHealth(400.0f);

    // Determine who cannot walk over this object:
    solidState |= SolidStateBits::PLAYER;

    addComponent(new IntertiaMover());
}

void LightTree::onCollision(Composite* other, CollisionData& collisionData) {
    //
    // Created running trees, amazing, but not usefull at all -- Gerjo.
    //
    //Vector3 direction = directionTo(static_cast<Entity*>(other));

    //Pulse pulse;
    //pulse.direction = direction.reverse();
    //pulse.friction  = 10;
    //pulse.speed     = 200;

    //Message<Pulse> message("add-pulse", pulse);
    //handleMessage(&message);
}