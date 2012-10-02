#include "Soldier.h"

using namespace phantom;

Soldier::Soldier() :
        _velocity(10, 10, 0),
        _isSelected(false)
{
    draw();
}

void Soldier::draw(void) {

    getGraphics().clear();

    getGraphics()
        .beginPath()
        .setFillStyle(Color::BLACK)
        .rect(0, 0, 12, 12)

        .beginPath()
        .setFillStyle(Color::WHITE)
        .arc(6.0f, 6.0f, 4.0f, 0.0f, 2 * M_PI)
        .beginPath();

    if(_isSelected) {
        getGraphics()
        .beginPath()
        .setFillStyle(Color::BLACK)
        .arc(6.0f, 6.0f, 20.0f, 0.0f, 2 * M_PI)
        .beginPath()
        .setFillStyle(Color::HOTPINK)
        .arc(6.0f, 6.0f, 19.0f, 0.0f, 2 * M_PI)
        .beginPath();
    }
}

void Soldier::update(const float& elapsed) {
    InputState* meh     = InputState::getMe();
    MouseState* mouse   = meh->getMouseState();
    const Vector3f& pos = mouse->getMousePosition();

    if(mouse->isButtonDown(MouseState::BUTTON_LEFT)) {
        _target.x() = pos.x();
        _target.y() = pos.y();
    }

    Vector3f diff = (_target - _position) * 0.1;

    setX(_position.x() + diff.x());
    setY(_position.y() + diff.y());
}

void Soldier::setSelected(bool isSelected) {
    _isSelected = isSelected;

    draw();
}
