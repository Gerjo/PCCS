#include "HeavyCrate.h"
#include "../components/Console.h"
#include <messaging/Message.h>

HeavyCrate::HeavyCrate(){
    repaint();
    setBoundingBox(Box3(0,0,150,150));
}
void HeavyCrate::onCollision(Composite* other){
    LightCrate::onCollision(other);
}
void HeavyCrate::paint(){
    getGraphics().clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/pickups/crate150x150.png", 0, 0, 150,150)
        .stroke()
        ;
}
