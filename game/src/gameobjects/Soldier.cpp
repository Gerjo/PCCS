#include "Soldier.h"

using namespace phantom;

Soldier::Soldier() :
_velocity(10, 10, 0),
_isSelected(false) {
    draw();

    setX(200);
    setY(200);

    _target = _position;
}

void Soldier::draw(void) {
    getGraphics().clear();

    getGraphics()
            .beginPath()
            .setFillStyle(Colors::BLACK)
            .rect(-6.0f, -6.0f, 12, 12)
            .stroke()

            .beginPath()
            .setFillStyle(Colors::WHITE)
            .arc(0.0f, 0.0f, 4.0f, 0.0f, 2 * M_PI)
            .stroke();

    if (isSelected()) {
        getGraphics()
                .beginPath()
                .setFillStyle(Colors::BLACK)
                .arc(0.0f, 0.0f, 7.0f, 0.0f, 2 * M_PI)
                .stroke()
                .beginPath()
                .setFillStyle(Colors::HOTPINK)
                .arc(0.0f, 0.0f, 8.0f, 0.0f, 2 * M_PI)
                .stroke();
    }
}

void Soldier::update(const float& elapsed) {
    Vector3f diff = (_target - _position) * 0.2 * elapsed;

    
}

void Soldier::setSelected(bool isSelected) {
    _isSelected = isSelected;

    draw();
}

void Soldier::setTarget(Vector3f target) {
    _target = target;
}

bool Soldier::isSelected(void) {
    return _isSelected;
}