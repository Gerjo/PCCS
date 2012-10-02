#include "Soldier.h"

using namespace phantom;

Soldier::Soldier() :
        _velocity(10, 10, 0) {
    draw();

}

void Soldier::draw(void) {
    getGraphics().
        beginPath().
        setFillStyle(Color(127, 0, 0, 127)).
        arc(6, 6, 6, 0, (2 * M_PI)).
        beginPath();
}

void Soldier::update(const float& elapsed) {

    setX(_position.x() + _velocity.x() * elapsed);
    setY(_position.y() + _velocity.y() * elapsed);

    InputState* meh = InputState::getMe();

    cout << (int)meh->getMouseState()->isButtonDown(0) << endl;
}
