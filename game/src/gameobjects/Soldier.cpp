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
    const string filename("images/gunner20x32.png");
    getGraphics().clear();

    getGraphics()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .rect(0, 0, _boundingBox.size.x, _boundingBox.size.y)
        .image(filename, -10, -16, 20, 32)
        ;

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

void Soldier::setPath(const vector<Vector3*> *path) {
    _path = *path;
    mover->moveTo(&_path);
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
}

void Soldier::onSelect(void) {
    setSelected(true);
}

void Soldier::onDeselect(void) {
    setSelected(false);
}

void Soldier::walk(Vector3 location) {
    Vector3 soldierPos = getPosition();

    Pathfinding* pathfinding = static_cast<Game*>(getGame())->getPathfinding();

    vector<Vector3*>* memleakage = new vector<Vector3*>();
    deque<Space*> spaces = pathfinding->getPath(soldierPos, location);

    memleakage->push_back(new Vector3(location));
    const int endOffset = 2; // Will pop the last element.

    for(int i = spaces.size() - endOffset; i >= 0; --i) {
        memleakage->push_back(new Vector3(spaces[i]->getCenter()));
    }

    setPath(memleakage);
}

void Soldier::attack(GameObject* object) {
    cout << "En garde!" << endl;
}