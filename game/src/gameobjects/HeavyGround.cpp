#include "HeavyGround.h"

HeavyGround::HeavyGround() {
    paint();
}

HeavyGround::~HeavyGround() {
}

void HeavyGround::paint() {
    getGraphics().beginPath().setFillStyle(Colors::WHITE);
    getGraphics().image("images/environment/ground_tile.png", 0.0f, 0.0f, 600, 600);
    getGraphics().fill();
}