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
        arc(6, 6, 6, 0, (2 * M_PI)).
        beginPath();
}
