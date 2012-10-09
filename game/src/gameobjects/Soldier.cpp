#include "Soldier.h"
#include "../Game.h"

using namespace phantom;

Soldier::Soldier() :
_isSelected(false),
_hasCollision(false),
_newCollisionState(false),
_target(_position)
{
    setType("Soldier");
    draw();
    addComponent(new Mover());
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

    getGraphics().beginPath().setLineStyle(Colors::BLACK);

    if(_path.size() > 1) {
        Vector3* prev = _path.front();
        for(size_t i = 1; i < _path.size(); ++i) {
            Vector3* center = _path[i];

            getGraphics().line(
                    prev->x - _position.x,
                    prev->y - _position.y,
                    center->x - _position.x,
                    center->y - _position.y).stroke();

            prev = center;
        }

        getGraphics().stroke();
    }
}

void Soldier::update(const float& elapsed) {
    GameObject::update(elapsed);

     draw();
    _hasCollision = false;
}

void Soldier::setSelected(bool isSelected) {
    _isSelected = isSelected;
}

void Soldier::setTarget(Vector3 target) {
    //if(mover != 0){
    //    mover->moveTo(& target);
    //}else{
    //    cout << "no mover attached" << endl;
    //}
}

void Soldier::setPath(vector<Vector3*> path) {
    _path = path;
    mover->moveTo(path);
}

bool Soldier::isSelected(void) {
    return _isSelected;
}

void Soldier::onCollision(Composite* other) {
    _hasCollision = true;
}