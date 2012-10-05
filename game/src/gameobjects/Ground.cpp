#include "Ground.h"

Ground::Ground() {
    draw();
}

void Ground::draw(void) {
    getGraphics()
            .setFillStyle(Colors::BLACK)
            .rect(0, 0, 50, 50)
            .stroke()

            .beginPath()
            .setFillStyle(Colors::BROWN)
            .rect(1, 1, 48, 48)
            .stroke()
    ;
}

void Ground::update(const float& elapsed) {

}
