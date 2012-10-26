#include "Selector.h"
#include <sharedlib/pathfinding/BSPTree.h>
#include "../Game.h"
#include "../gamestates/ClientWorld.h"
#include "Cursor.h"

Selector::Selector() : _trackingLayer(0), _camera(0), _doRedraw(true) {

}

Selector::~Selector() {

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

void Selector::setCamera(Camera* camera) {
    _camera = camera;
}

void Selector::handleHover(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState) {
    vector<Entity*> entities;
    _trackingLayer->getEntitiesAt(entities, worldLocation);

    string tooltip;

    for(size_t i = 0; i < entities.size(); ++i) {
        GameObject* gob = static_cast<GameObject*>(entities[i]);

        if(gob->canHover()) {
            gob->onMouseHover(worldLocation, screenLocation);
        }

        tooltip = gob->getType();
    }

    getGame<Game*>()->world->cursor->setTooltip(tooltip);
}

void Selector::update(const Time& time) {
    if(_camera == 0) {
        return;
    }

    MouseState* mouseState = getDriver()->getInput()->getMouseState();
    Vector3 screenLocation = mouseState->getMousePosition();
    Vector3 worldLocation  = _camera->getWorldCoordinates(mouseState->getMousePosition());

    handleHover(worldLocation, screenLocation, *mouseState);
    handleSelection(worldLocation, screenLocation, *mouseState);



    setPosition(_selectionBox.origin);

    drawSelection();
}

void Selector::setTrackingLayer(BSPTree* layer) {
    _trackingLayer = layer;
}

void Selector::handleSelection(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState) {

    if (mouseState.isButtonDown(Buttons::LEFT_MOUSE)) {

        // Take the selector start location:
        if (!_hasSelectionStart) {
            _selectionBox.origin = worldLocation;
            _selectionBox.size.x = _selectionBox.size.y = 0;
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
            vector<Entity*> entities;
            _trackingLayer->getEntitiesAt(entities, worldLocation);

            bool changeSelection = false;

            for(int i = entities.size() - 1; i >= 0 ; --i) {
                GameObject* gameObject = static_cast<GameObject*>(entities[i]);

                if(gameObject->isType("Soldier")) {
                    HeavySoldier* soldier = static_cast<HeavySoldier*>(gameObject);

                    if(soldier->isMe()) {
                        deSelect();
                        _hasFinalizedSelection = true;
                        gameObject->onSelect();
                        changeSelection = true;
                        break;
                    }
                }
            }

            if(!changeSelection) {
                click(worldLocation, screenLocation, mouseState);
            }
        }

    // Cancellation of selection:
    } else if (mouseState.isButtonDown(Buttons::RIGHT_MOUSE)) {
        _hasSelectionStart = false;
        _doRedraw = true;
        deSelect();
    }
}

MessageState Selector::handleMessage(AbstractMessage* message) {
    if(message->isType("selector-register")) {
        HeavySoldier* soldier = message->getPayload<HeavySoldier*>();

        if(std::find(_soldiers.begin(), _soldiers.end(), soldier) == _soldiers.end()) {
            _soldiers.push_back(soldier);
        }

        return CONSUMED;

    // NB: Unregister is untested at the time of writing.
    } else if(message->isType("selector-unregister")) {
        HeavySoldier* soldier = message->getPayload<HeavySoldier*>();

        deque<HeavySoldier*>::iterator location = std::find(_soldiers.begin(), _soldiers.end(), soldier);

        if(location != _soldiers.end()) {
            _soldiers.erase(location);
        }

        return CONSUMED;
    }

    return Composite::handleMessage(message);
}

void Selector::deSelect(void) {

    for(HeavySoldier* soldier : _soldiers) {
        soldier->onDeselect();
    }

    _hasFinalizedSelection = false;
}

void Selector::finalize() {
    deSelect();

    _selectionBox.repair();

    for(HeavySoldier* soldier : _soldiers) {
        Vector3 worldPos = soldier->getPosition();

        bool isSelected = false;

        if(_selectionBox.intersect(soldier->getBoundingBox())) {
            isSelected = true;
            _hasFinalizedSelection = true;

            soldier->onSelect();
        }
    }
}

void Selector::click(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState) {

    // Don't bother with anything if there are no selected units.
    if (_hasFinalizedSelection) {
        bool doAttack = false;

        GameObject* object = 0;
        vector<Entity*> entities;
        _trackingLayer->getEntitiesAt(entities, worldLocation);

        for(size_t i = 0; i < entities.size(); ++i) {
            object = static_cast<GameObject*>(entities[i]);
            doAttack = true;
            break;
        }

        for(HeavySoldier* soldier : _soldiers) {
            if(soldier->isSelected()) {
                if(doAttack) {
                    soldier->attack(object);
                } else {
                    soldier->walk(Vector3(worldLocation));
                }
            }
        }
    }
}