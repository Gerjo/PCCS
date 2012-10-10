#include "Selector.h"

#include "../gameobjects/Soldier.h"
#include "../Game.h"

Selector::Selector(BSPTree& layer) :
    _layer(layer),
    _hasSelectionStart(false),
    _hasFinalizedSelection(false)
{

}

void Selector::drawSelection(void) {
    getGraphics().clear();

    // Conditionally show the selection.
    if (_hasSelectionStart) {
        getGraphics()
                .beginPath()
                .setFillStyle(Color(127, 127, 127, 30))
                .rect(0, 0, _selectionBox.size.x, _selectionBox.size.y)
                .stroke();
    }
}

void Selector::handleHover(Vector3& worldLocation, Vector3& screenLocation) {
    vector<Entity*> entities;
    _layer.getEntitiesAt(entities, worldLocation);

    for(size_t i = 0; i < entities.size(); ++i) {
        GameObject* gob = static_cast<GameObject*>(entities[i]);

        if(gob->canHover()) {
            gob->onMouseHover(worldLocation, screenLocation);
        }
    }
}

void Selector::update(const float& elapsed) {
    Game* game             = static_cast<Game*>(getGame());
    Camera& camera         = game->getRtsCamera().getPhantomCamera();
    MouseState* mouseState = getDriver()->getInput()->getMouseState();
    Vector3 screenLocation = mouseState->getMousePosition();
    Vector3 worldLocation  = camera.getWorldCoordinates(mouseState->getMousePosition());

    handleHover(worldLocation, screenLocation);

    bool doRedraw = false;

    // Selection of units:
    if (mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
        if (!_hasSelectionStart) {
            _selectionBox.origin    = camera.getWorldCoordinates(mouseState->getMousePosition());
            _hasSelectionStart   = true;
            start();
        } else {
            Vector3 newSize = camera.getWorldCoordinates(mouseState->getMousePosition()) - _selectionBox.origin;

            // The user is "dragging" his mouse.
            if (newSize != _selectionBox.size) {
                _selectionBox.size = newSize;
                doRedraw = true;
            }
        }

    } else {
        if (_hasSelectionStart) {
            _hasSelectionStart = false;
            doRedraw = true;

            // Only finish a selection if the selected area is greater than
            // the threshold. This is useful for people who quickly click whilst
            // the mouse is still moving. You want this click to be a click, and
            // not the start of a new selection;
            const float threshold = 2.0f;

            if (abs(_selectionBox.size.x) > threshold &&
                    abs(_selectionBox.size.y) > threshold) {

                finalize();
                doRedraw = true;
            } else {
                click();
                doRedraw = true;
            }
        }
    }

    setPosition(_selectionBox.origin);

    if (mouseState->isButtonDown(Buttons::RIGHT_MOUSE)) {
        _hasSelectionStart = false;
        doRedraw = true;

        cancel();
    }

    if (doRedraw) {
        drawSelection();
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

    _selectionBox.repair();

    for (; it != _soldiers.end(); ++it) {
        Soldier* soldier = *it;
        Vector3 worldPos = soldier->getPosition();

        bool isSelected = false;

        if(_selectionBox.intersect(soldier->getBoundingBox())) {
            isSelected = true;
            _hasFinalizedSelection = true;
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

    _hasFinalizedSelection = false;

}

void Selector::click(void) {
    if (_hasFinalizedSelection) {
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