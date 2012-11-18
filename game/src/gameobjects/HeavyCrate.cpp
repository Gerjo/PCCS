#include "HeavyCrate.h"
#include <messaging/Message.h>

HeavyCrate::HeavyCrate() {
    repaint();
}

void HeavyCrate::onCollision(Composite* other) {
    LightCrate::onCollision(other);
}

void HeavyCrate::paint() {
    getGraphics().clear()
            .beginPath()
            .setFillStyle(Colors::WHITE)
            .image("images/pickups/crate150x150.png", 0, 0, _boundingBox.size.x,  _boundingBox.size.y)
            .stroke()
            ;
}
