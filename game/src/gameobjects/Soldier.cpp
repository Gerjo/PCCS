#include "Soldier.h"
#include "../Game.h"

using namespace phantom;

Soldier::Soldier() :
    _isSelected(false),
    _hasCollision(false),
    _newCollisionState(false),
    _showPath(false),
    _doRedraw(true),
    _isHovering(false)
{
    setType("Soldier");

    _victim   = 0;
    _canHover = true;
    _weapon   = new Weapon();

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
        getGraphics().beginPath().setFillStyle(Color(0, 0, 0, 50));
        Vector3* prev = &_path.front();
        for(size_t i = 1; i < _path.size(); ++i) {
            Vector3* center = &_path[i];

            getGraphics().line(
                    prev->x - _position.x,
                    prev->y - _position.y,
                    center->x - _position.x,
                    center->y - _position.y).stroke();

            prev = center;
        }

        getGraphics().fill();
    }
}

void Soldier::update(const float& elapsed) {
    GameObject::update(elapsed);

    handleAi();

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
    _victim = 0;
    seekRoute(location);

    stringstream ss;

    if(_path.empty()) {
        ss << "Cannot find route to destination.";
    } else {
        ss << "Walking to location (" << _path.size() << " waypoints).";
    }

    Console::log(ss.str());
}

bool Soldier::seekRoute(Vector3 location) {
    Vector3 soldierPos = getPosition();

    Pathfinding* pathfinding = static_cast<Game*>(getGame())->getPathfinding();

    _path.clear();
    deque<Space*> spaces = pathfinding->getPath(soldierPos, location);

    if(spaces.empty()) {
        return false;
    }

    _path.push_back(Vector3(location));

    // We pop the last element, walking to the mouse coords is more
    // sensible than walking to the waypoint. NB: '2' is intentional.
    const int endOffset = 2;

    for(int i = spaces.size() - endOffset; i >= 0; --i) {
        _path.push_back(Vector3(spaces[i]->getCenter()));
    }

    mover->moveTo(_path);
    setShowPath(true);

    return true;
}

void Soldier::attack(GameObject* victim) {
    _victim = victim;

    if(victim->isType("Enemy")) {
        bool foundPath = seekRoute(_victim->getPosition());

        // Walk towards our enemy.
        if(foundPath) {
            Console::log("Attacking enemy.");
        } else {
            Console::log("Unable to attack, cannot find route.");
        }
    }
}

void Soldier::handleAi(void) {
    if(_victim != 0) {
        float distanceSq = distanceToSq(_victim);
        if(distanceSq < _weapon->getRangeSq()) {


            if(!mover->isStopped()) {
                mover->stop();
                Console::log("*fires bullets and stuff.*");
            }
        }
    }
}

void Soldier::setShowPath(bool isVisible) {
    _showPath = isVisible;
}
