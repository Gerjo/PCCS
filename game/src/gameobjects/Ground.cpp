#include "Ground.h"

Ground::Ground() {
    draw();
}

void Ground::draw(void) {
    getGraphics()
            .setFillStyle(Colors::BLACK)
            .rect(0, 0, 12, 12)
            .stroke()

            .beginPath()
            .setFillStyle(Colors::BROWN)
            .rect(1, 1, 11, 11)
            .stroke()
    ;
}

void Ground::update(const float& elapsed) {

}
