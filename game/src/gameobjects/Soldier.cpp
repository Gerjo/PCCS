#include "Soldier.h"

using namespace phantom;

Soldier::Soldier() :
        _velocity(100, 100, 0) {
    draw();

}

void Soldier::draw(void) {
    getGraphics().
        beginPath().
        setFillStyle(Color(127, 0, 0, 127)).
        arc(6.0f, 6.0f, 6.0f, 0.0f, static_cast<float>(2 * M_PI)).
        beginPath();
}

void Soldier::update(const float& elapsed) {
    setX(_position.x() + _velocity.x() * elapsed);
    setY(_position.y() + _velocity.y() * elapsed);

    InputState* meh      = InputState::getMe();
    MouseState* mouse    = meh->getMouseState();
    const Eigen::Vector2f& pos = *mouse->getMousePosition();

    //cout << (int)mouse->isButtonDown(0) << pos.x() << " " << pos.y() << endl;
}
