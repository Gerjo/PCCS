#include "HeavyWater.h"

HeavyWater::HeavyWater() {
    repaint();
}

HeavyWater::~HeavyWater() {

}

void HeavyWater::paint(void) {
    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/environment/water_tile.png", 0, 0, 200, 200)
        .fill()
        .stroke()
        ;
}