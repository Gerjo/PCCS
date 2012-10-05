#include "Soldier.h"

using namespace phantom;

Soldier::Soldier() :
_isSelected(false),
_hasCollision(false),
_newCollisionState(false),
_target(_position)
{
    draw();
    setX(200);
    setY(200);
}

void Soldier::draw(void) {
    getGraphics().clear();

    getGraphics()
            .beginPath()
            .setFillStyle(Colors::BLACK)
            .rect(-6.0f, -6.0f, 12, 12)
            .stroke();

    if(_hasCollision) {
        getGraphics()
            .beginPath()
            .setFillStyle(Colors::RED)
            .rect(-6.0f, -6.0f, 12, 12)
            .stroke();
    }

    if (isSelected()) {
        getGraphics()
                .beginPath()
                .setFillStyle(Colors::BLACK)
                .arc(0.0f, 0.0f, 7.0f, 0.0f, 2 * 3.14159f)
                .stroke()
                .beginPath()
                .setFillStyle(Colors::HOTPINK)
                .arc(0.0f, 0.0f, 8.0f, 0.0f, 2 * 3.14159f)
                .stroke();
    }
}

void Soldier::update(const float& elapsed) {
    Vector3 diff = (_target - _position) * 0.4 * elapsed;

    setX(_position.x + diff.x);
    setY(_position.y + diff.y);

    draw();
    _hasCollision = false;
}

void Soldier::setSelected(bool isSelected) {
    _isSelected = isSelected;
}

void Soldier::setTarget(Vector3 target) {
    _target = target;

}

bool Soldier::isSelected(void) {
    return _isSelected;
}

void Soldier::onCollision(Composite* other) {
    _hasCollision = true;
}