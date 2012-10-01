#include "Ground.h"

Ground::Ground() {
    draw();
}

void Ground::draw(void) {
    Graphics& gfx = getGraphics();
    gfx.setFillStyle(phantom::Color(0, 0, 0, 127));
    gfx.rect(0, 0, 12, 12);
    gfx.beginPath();

    gfx.setFillStyle(phantom::Color(50, 10, 0, 127));
    gfx.rect(1, 1, 11, 11);
    gfx.beginPath();
}