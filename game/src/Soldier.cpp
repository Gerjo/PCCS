#include "Soldier.h"

using namespace phantom;

Soldier::Soldier() {
    isMovingRight = true;

    draw();
    this->getPosition();
}

void Soldier::draw(void) {
    getGraphics()->beginPath();
    getGraphics()->setFillStyle(phantom::Color(127, 0, 0, 127));
    getGraphics()->setLineStyle(phantom::Color(0, 127, 0, 127));

    getGraphics()->arc(0, 250, 100, 0, (2 * M_PI));
    getGraphics()->arc(0, 100, 50, 0, (2 * M_PI));

    getGraphics()->beginPath();
}

void Soldier::update(const float& elapsed) {
    if(isMovingRight) {
        _position.x() += 5;

        if(_position.x() > 500) {
            isMovingRight = !isMovingRight;
        }

    } else {
        _position.x() -= 5;

        if(_position.x() < 100) {
            isMovingRight = !isMovingRight;
        }
    }
}
