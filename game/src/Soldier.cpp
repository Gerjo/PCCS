#include "Soldier.h"

Soldier::Soldier() {
    x = 0;
    y = 0;

    isMovingRight = true;
}

void Soldier::draw(void) {

    getGraphics()->clear();

    getGraphics()->beginPath();
    getGraphics()->setFillStyle(phantom::Color(127, 0, 0, 127));
    getGraphics()->setLineStyle(phantom::Color(0, 127, 0, 127));

    getGraphics()->arc(x, 250, 100, 0, (2 * M_PI));
    getGraphics()->arc(x, 100, 50, 0, (2 * M_PI));

    getGraphics()->beginPath();
}

void Soldier::update(const float& elapsed) {
    draw();


    if(isMovingRight) {
        x += 5;

        if(x > 500) {
            isMovingRight = !isMovingRight;
        }

    } else {
        x -= 5;

        if(x < 100) {
            isMovingRight = !isMovingRight;
        }
    }

}
