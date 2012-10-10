#include "Selector.h"

#include "../gameobjects/Soldier.h"
#include "../Game.h"

Selector::Selector(BSPTree& layer) :
    _layer(layer),
    _hasSelectionStart(false),
    _hasFinalizedSelection(false),
    _doRedraw(true),
    _camera(static_cast<Game*>(getGame())->getRtsCamera().getPhantomCamera())
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

void Selector::handleHover(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState) {
    vector<Entity*> entities;
    _layer.getEntitiesAt(entities, worldLocation);

    for(size_t i = 0; i < entities.size(); ++i) {
        GameObject* gob = static_cast<GameObject*>(entities[i]);

        if(gob->canHover()) {
            gob->onMouseHover(worldLocation, screenLocation);
        }
    }
}

void Selector::handleSelection(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState) {

    if (mouseState.isButtonDown(Buttons::LEFT_MOUSE)) {

        // Take the selector start location:
        if (!_hasSelectionStart) {
            _selectionBox.origin = worldLocation;
            _hasSelectionStart   = true;

        // Update the selector size:
        } else {
            Vector3 newSize = worldLocation - _selectionBox.origin;

            // The user is "dragging" his mouse.
            if (newSize != _selectionBox.size) {
                _selectionBox.size = newSize;
                _doRedraw = true;
            }
        }

    // Mouse up:
    } else if (_hasSelectionStart) {
        _hasSelectionStart = false;
        _doRedraw = true;

        if(_selectionBox.size.getLengthSq() > 4) {
            finalize();
        } else {
            click();
        }

    // Cancellation of selection:
    } else if (mouseState.isButtonDown(Buttons::RIGHT_MOUSE)) {
        _hasSelectionStart = false;
        _doRedraw = true;
        deSelect();
    }
}

void Selector::update(const float& elapsed) {
    MouseState* mouseState = getDriver()->getInput()->getMouseState();
    Vector3 screenLocation = mouseState->getMousePosition();
    Vector3 worldLocation  = _camera.getWorldCoordinates(mouseState->getMousePosition());

    handleHover(worldLocation, screenLocation, *mouseState);
    handleSelection(worldLocation, screenLocation, *mouseState);

    if (_doRedraw) {
        setPosition(_selectionBox.origin);
        drawSelection();
    }
}

void Selector::addSoldier(Soldier* soldier) {
    _soldiers.push_back(soldier);
}

void Selector::finalize() {
    deSelect();

    _selectionBox.repair();

    deque<Soldier*>::iterator it = _soldiers.begin();
    for (; it != _soldiers.end(); ++it) {
        Soldier* soldier = *it;
        Vector3 worldPos = soldier->getPosition();

        bool isSelected = false;

        if(_selectionBox.intersect(soldier->getBoundingBox())) {
            isSelected = true;
            _hasFinalizedSelection = true;

            soldier->onSelect();
        }
    }
}

void Selector::deSelect(void) {
    deque<Soldier*>::iterator it = _soldiers.begin();

    for (; it != _soldiers.end(); ++it) {
        (*it)->onDeselect();
    }

    _hasFinalizedSelection = false;
}

void Selector::click(void) {
    if (_hasFinalizedSelection) {
        MouseState* mouse = getGame()->getDriver()->getInput()->getMouseState();
        Vector3 pos       = _camera.getWorldCoordinates(mouse->getMousePosition());

        deque<Soldier*>::iterator it = _soldiers.begin();

        Pathfinding* pathfinding = static_cast<Game*>(getGame())->getPathfinding();

        for (; it != _soldiers.end(); ++it) {
            Soldier* soldier = *it;
            Vector3 soldierPos = soldier->getPosition();

            if (soldier->isSelected()) {
                vector<Vector3*> memleakage;
                deque<Space*> spaces = pathfinding->getPath(soldierPos, pos);

                memleakage.push_back(new Vector3(pos));
                int endOffset   = 2; // Will pop the last element.

                for(int i = spaces.size() - endOffset; i >= 0; --i) {
                    memleakage.push_back(new Vector3(spaces[i]->getCenter()));
                }

                soldier->setPath(memleakage);
            }
        }
    }
}