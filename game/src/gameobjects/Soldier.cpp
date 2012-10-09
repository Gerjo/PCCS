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
    if(_route.size() > 1) {
        Vector3 prev = _route.front()->getCenter();
        for(size_t i = 1; i < _route.size(); ++i) {
            Vector3 center = _route[i]->getCenter();

            getGraphics().line(prev.x - _position.x, prev.y - _position.y, center.x - _position.x, center.y - _position.y).stroke();

            prev = center;

        }

        getGraphics().stroke();
    }
}

void Soldier::update(const float& elapsed) {
    GameObject::update(elapsed);
    draw();
    _hasCollision = false;

    Camera& cam       = static_cast<Game*>(getGame())->getRtsCamera().getPhantomCamera();
    MouseState* mouse = getDriver()->getInput()->getMouseState();

    if(!mouse->isButtonDown(Buttons::LEFT_MOUSE) || !isSelected()) {
        return;
    }

    Pathfinding* pathfinding = static_cast<Game*>(getGame())->getPathfinding();

    Vector3 goal = cam.getWorldCoordinates(mouse->getMousePosition());

    _route = pathfinding->getPath(_position, goal);

    if(_route.size() == 0) {
        //cout << " No route possible. " << endl;
    } else {
        
    }
}

void Soldier::setSelected(bool isSelected) {
    _isSelected = isSelected;
}

void Soldier::setTarget(Vector3 target) {
    //mover->moveTo(&target);
}

bool Soldier::isSelected(void) {
    return _isSelected;
}

void Soldier::onCollision(Composite* other) {
    _hasCollision = true;
}