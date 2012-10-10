#include "Selector.h"

#include "../gameobjects/Soldier.h"
#include "../Game.h"

Selector::Selector() :
    _hasStartpoint(false),
    _hasSelection(false)
{

}

void Selector::draw(void) {
    getGraphics().clear();

    // Conditionally show the selection.
    if (_hasStartpoint) {
        getGraphics()
                .beginPath()
                .setFillStyle(Color(127, 127, 127, 30))
                .rect(0, 0, _world.size.x, _world.size.y)
                .stroke();
    }
}

void Selector::update(const float& elapsed) {

    Game* game  = static_cast<Game*>(getGame());
    Camera& cam = game->getRtsCamera().getPhantomCamera();

    MouseState* mouse = getDriver()->getInput()->getMouseState();

    bool doRedraw = false;

    // Selection of units:
    if (mouse->isButtonDown(Buttons::LEFT_MOUSE)) {
        if (!_hasStartpoint) {
            _world.origin    = cam.getWorldCoordinates(mouse->getMousePosition());
            _hasStartpoint   = true;
            start();
        } else {
            Vector3 newSize = cam.getWorldCoordinates(mouse->getMousePosition()) - _world.origin;

            // The user is "dragging" his mouse.
            if (newSize != _world.size) {
                _world.size = newSize;
                doRedraw = true;
            }
        }

    } else {
        if (_hasStartpoint) {
            _hasStartpoint = false;
            doRedraw = true;

            // Only finish a selection if the selected area is greater than
            // the threshold. This is useful for people who quickly click whilst
            // the mouse is still moving. You want this click to be a click, and
            // not the start of a new selection;
            const float threshold = 2.0f;

            if (abs(_world.size.x) > threshold &&
                    abs(_world.size.y) > threshold) {

                finalize();
                doRedraw = true;
            } else {
                click();
                doRedraw = true;
            }
        }
    }

    setPosition(_world.origin);

    if (mouse->isButtonDown(Buttons::RIGHT_MOUSE)) {
        _hasStartpoint = false;
        doRedraw = true;

        cancel();
    }

    if (doRedraw) {
        draw();
    }
}

void Selector::addSoldier(Soldier* soldier) {
    _soldiers.push_back(soldier);
}

void Selector::start(void) {
    //cout << "start" << endl;
}

void Selector::finalize() {
    deque<Soldier*>::iterator it = _soldiers.begin();

    _world.repair();

    for (; it != _soldiers.end(); ++it) {
        Soldier* soldier = *it;
        Vector3 worldPos = soldier->getPosition();

        bool isSelected = false;

        if(_world.intersect(soldier->getBoundingBox())) {
            isSelected = true;
            _hasSelection = true;
        }

        soldier->setSelected(isSelected);
    }
}

void Selector::cancel(void) {
    deque<Soldier*>::iterator it = _soldiers.begin();

    for (; it != _soldiers.end(); ++it) {
        Soldier* soldier = *it;

        soldier->setSelected(false);
    }

    _hasSelection = false;

}

void Selector::click(void) {
    if (_hasSelection) {
        MouseState* mouse = getGame()->getDriver()->getInput()->getMouseState();
        Vector3 pos = mouse->getMousePosition();

        Game* game  = static_cast<Game*>(getGame());
        Camera& cam = game->getRtsCamera().getPhantomCamera();

        pos = cam.getWorldCoordinates(pos);

        float soldierOffset = 1;
        deque<Soldier*>::iterator it = _soldiers.begin();

        Pathfinding* pathfinding = game->getPathfinding();

        for (; it != _soldiers.end(); ++it) {
            Soldier* soldier = *it;
            Vector3 soldierPos = soldier->getPosition();

            if (soldier->isSelected()) {
                vector<Vector3*> memleakage;
                deque<Space*> spaces = pathfinding->getPath(soldierPos, pos);

                // NB: There shall always be a route. We're manually
                // adding the click location as the last node. Yes, this will
                // mean the user can go-offscreen (for time being)
                //if(spaces.empty()) {
                //    cout << "No route found." << endl;
                //    continue;
                //}

                memleakage.push_back(new Vector3(pos));
                int startOffset = 0;
                int endOffset   = 2; // Will pop the last element.

                for(int i = spaces.size() - endOffset; i >= startOffset; --i) {
                    memleakage.push_back(new Vector3(spaces[i]->getCenter()));

                    //cout << i << ": " << spaces[i]->getCenter().toString();
                }

                soldier->setPath(memleakage);

                // Give each soldier a slight offset, this way they won't sit
                // on top of each other.
                soldierOffset += 0.05f;
            }
        }
    }
}