#include "Ground.h"

Ground::Ground() {
    draw();
}

void Ground::draw(void) {
    getGraphics()
    .setFillStyle(Color::BLACK)
    .rect(0, 0, 12, 12)
    .beginPath()
    .setFillStyle(Color::BROWN)
    .rect(1, 1, 11, 11)
    .beginPath();
}

void Ground::update(const float& elapsed) {

}
