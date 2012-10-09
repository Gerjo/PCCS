#include "Soldier.h"
#include <physics/Mover.h>
using namespace phantom;

Soldier::Soldier() :
_isSelected(false),
_hasCollision(false),
_newCollisionState(false),
_target(_position)
{
    setType("Soldier");
    draw();
    setX(200);
    setY(200);
}

void Soldier::draw(void) {
    getGraphics().clear();

    if (isSelected()) {
        getGraphics()
                .beginPath()
                .setFillStyle(Colors::WHITE)
                .rect(-1.0f, -1.0f, 14.0f, 14.0f)
                .stroke();
    }

    getGraphics()
            .beginPath()
            .rect(0.0f, 0.0f, 12, 12);


    if(_hasCollision) {
        getGraphics().setFillStyle(Colors::RED);
    } else {
        getGraphics().setFillStyle(Colors::BLACK);
    }

    getGraphics().stroke();
}

void Soldier::update(const float& elapsed) {
    Composite::update(elapsed);
    draw();
    _hasCollision = false;
}

void Soldier::setSelected(bool isSelected) {
    _isSelected = isSelected;
}

void Soldier::setTarget(Vector3 target) {
    if(mover != 0){
        mover->moveTo(& target);
    }else{
        cout << "no mover attached" << endl;
    }
}

bool Soldier::isSelected(void) {
    return _isSelected;
}

void Soldier::onCollision(Composite* other) {
    _hasCollision = true;
}