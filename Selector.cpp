#include "Selector.h"

//#include "../gameobjects/Soldier.h"
#include "../Game.h"

Selector::Selector(BSPTree& layer) :
    _layer(layer),
    _hasSelectionStart(false),
    _hasFinalizedSelection(false),
    _doRedraw(true)//,
    //_camera(static_cast<Game*>(getGame())->getRtsCamera().getPhantomCamera())
{
    //_game = static_cast<Game*>(getGame());
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

    string tooltip;

    for(size_t i = 0; i < entities.size(); ++i) {
        GameObject* gob = static_cast<GameObject*>(entities[i]);

        if(gob->canHover()) {
            gob->onMouseHover(worldLocation, screenLocation);
        }

        tooltip = gob->getType();
    }

    //_game->getCursor()->setTooltip(tooltip);
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
            _layer.getEntitiesAt(entities, worldLocation);

            bool changeSelection = false;

            for(int i = entities.size() - 1; i >= 0 ; --i) {
                GameObject* gameObject = static_cast<GameObject*>(entities[i]);

                if(gameObject->isType("Soldier")) {
                    deSelect();
                    _hasFinalizedSelection = true;
                    gameObject->onSelect();
                    changeSelection = true;
                    break;
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

void Selector::update(const float& elapsed) {
    MouseState* mouseState = getDriver()->getInput()->getMouseState();
    Vector3 screenLocation = mouseState->getMousePosition();
    Vector3 worldLocation  = _camera.getWorldCoordinates(mouseState->getMousePosition());

    handleHover(worldLocation, screenLocation, *mouseState);
    handleSelection(worldLocation, screenLocation, *mouseState);

    setPosition(_selectionBox.origin);

    drawSelection();
}

void Selector::finalize() {
    deSelect();

    _selectionBox.repair();

    /*auto it = _soldiers.begin();
    for (; it != _soldiers.end(); ++it) {
        Soldier* soldier = *it;
        Vector3 worldPos = soldier->getPosition();

        bool isSelected = false;

        if(_selectionBox.intersect(soldier->getBoundingBox())) {
            isSelected = true;
            _hasFinalizedSelection = true;

            soldier->onSelect();
        }
    }*/
}

void Selector::deSelect(void) {
    //deque<Soldier*>::iterator it = _soldiers.begin();

    //for (; it != _soldiers.end(); ++it) {
    //    (*it)->onDeselect();
   // }

    _hasFinalizedSelection = false;
}

void Selector::click(Vector3& worldLocation, Vector3& screenLocation, MouseState& mouseState) {

    // Don't bother with anything if there are no selected units.
    if (_hasFinalizedSelection) {
        bool doAttack = false;

        GameObject* object = 0;
        vector<Entity*> entities;
        _layer.getEntitiesAt(entities, worldLocation);

        for(size_t i = 0; i < entities.size(); ++i) {
            object = static_cast<GameObject*>(entities[i]);
            doAttack = true;
            break;
        }

        /*deque<Soldier*>::iterator it = _soldiers.begin();
        for (; it != _soldiers.end(); ++it) {
            Soldier* soldier = *it;

            if(soldier->isSelected()) {
                if(doAttack) {
                    soldier->attack(object);
                } else {
                    soldier->walk(Vector3(worldLocation));
                }
            }
        }*/
    }
}

//void Selector::addSoldier(Soldier* soldier) {
//    _soldiers.push_back(soldier);
//}
