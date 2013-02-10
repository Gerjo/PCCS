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
        .image("images/environment/water_tile.png", 0, 0, 100, 100)
        .fill()
        .stroke()
        ;
}