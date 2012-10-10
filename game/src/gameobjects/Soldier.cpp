#include "Soldier.h"
#include "../Game.h"

using namespace phantom;

Soldier::Soldier() :
    _isSelected(false),
    _hasCollision(false),
    _newCollisionState(false),
    _target(_position),
    _showPath(false),
    _doRedraw(true),
    _isHovering(false)
{
    setType("Soldier");

    _canHover = true;

    addComponent(new Mover());
}

void Soldier::draw(void) {
    _doRedraw = false;
    getGraphics().clear();

    getGraphics()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .image("images/gunner20x32.png", -10, -16, 20, 32);

    if (_isSelected) {
        getGraphics().setFillStyle(Colors::BLUE);
    }

    if(_isHovering) {
        getGraphics().setFillStyle(Colors::RED);
    }

    getGraphics().fill();

    if(_showPath && _path.size() > 1) {
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

    if(_showPath) {
        _doRedraw = true;
    }

    if(_doRedraw) {
        draw();
    }

    // Reschedule a draw call for the next update() iteration:
    if(_isHovering || _hasCollision) {
        _doRedraw = true;
    }

    _isHovering   = false;
    _hasCollision = false;
}

void Soldier::setSelected(bool isSelected) {
    _doRedraw   = true;
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
    _doRedraw     = true;
    _hasCollision = true;
}

void Soldier::onMouseHover(const Vector3& mouseLocationWorld, const Vector3& mouseLocationScreen) {
    _doRedraw   = true;
    _isHovering = true;
    cout << time(NULL) << "teeeheee" << endl;
}