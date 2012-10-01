#include "Ground.h"

Ground::Ground() {
    draw();
}

void Ground::draw(void) {
    Graphics* gfx = getGraphics();
    getGraphics()->setFillStyle(phantom::Color(0, 0, 0, 127));
    gfx->rect(0, 0, 10, 10);
    gfx->beginPath();

    getGraphics()->setFillStyle(phantom::Color(50, 10, 0, 127));
    gfx->rect(1, 1, 9, 9);
    gfx->beginPath();
}