#include "HeavyCrate.h"

HeavyCrate::HeavyCrate(){
    repaint();
}

void HeavyCrate::paint(){
    getGraphics().clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/pickups/crate150x150.png", 0, 0, 150,150)
        .stroke()
        ;
}
