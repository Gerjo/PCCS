#include "Soldier.h"

using namespace phantom;

Soldier::Soldier() {
    draw();

    setX(12);
    setY(12);
}

void Soldier::draw(void) {
    getGraphics().
        beginPath().
        setFillStyle(Color(127, 0, 0, 127)).
        arc(6.0f, 6.0f, 6.0f, 0.0f, static_cast<float>(2 * M_PI)).
        beginPath();
}
