#include "Selector.h"

#include "gameobjects/Soldier.h"
#include "Game.h"

Selector::Selector() :
_startpoint(0, 0, 0),
_endpoint(0, 0, 0),
_hasStartpoint(false),
_hasSelection(false) {

}

void Selector::draw(void) {
    Game* game  = static_cast<Game*>(getGame());
    Camera& cam = game->getRtsCamera().getPhantomCamera();

    // translate this layer, too.
    _position   = cam.getPosition();

    getGraphics().clear();

    // Conditionally show the selection.
    if (_hasStartpoint) {
        getGraphics()
                .beginPath()
                .setFillStyle(Color(127, 127, 127, 30))
                .rect(_startpoint.x, _startpoint.y, _endpoint.x - _startpoint.x, _endpoint.y - _startpoint.y)
                .stroke();
    }
}

void Selector::update(const float& elapsed) {

    MouseState* mouse = getGame()->getDriver()->getInput()->getMouseState();

    bool doRedraw = false;
   // MouseState* mouse = InputState::getMe()->getMouseState();

    // Selection of units:
    if (mouse->isButtonDown(Buttons::LEFT_MOUSE)) {
        if (!_hasStartpoint) {
            _startpoint = mouse->getMousePosition();
            _endpoint   = _startpoint;
            _hasStartpoint = true;
            start();
        } else {
            // The user is "dragging" his mouse.
            if (_endpoint != mouse->getMousePosition()) {
                _endpoint = mouse->getMousePosition();
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

            if (abs(_endpoint.x - _startpoint.x) > threshold &&
                    abs(_endpoint.y - _startpoint.y) > threshold) {

                finalize();
                doRedraw = true;
            } else {
                click();
                doRedraw = true;
            }
        }
    }


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
    cancel();

    Game* game  = static_cast<Game*>(getGame());
    Camera& cam = game->getRtsCamera().getPhantomCamera();

    Vector3 upperbound(
            max(_startpoint.x, _endpoint.x),
            max(_startpoint.y, _endpoint.y)
            );

    Vector3 lowerbound(
            min(_startpoint.x, _endpoint.x),
            min(_startpoint.y, _endpoint.y)
            );


    upperbound = cam.getWorldCoordinates(upperbound);
    lowerbound = cam.getWorldCoordinates(lowerbound);

    deque<Soldier*>::iterator it = _soldiers.begin();



    //cout << world.toString() << endl;

    for (; it != _soldiers.end(); ++it) {
        Soldier* soldier = *it;
        Vector3 worldPos = soldier->getPosition();

        bool isSelected = false;

        if (worldPos.x > lowerbound.x && worldPos.x < upperbound.x) {
            if (worldPos.y > lowerbound.y && worldPos.y < upperbound.y) {
                isSelected = true;
                _hasSelection = true;
            }
        }

        soldier->setSelected(isSelected);
    }

    //cout << "finalize" << endl;
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

        float offset = 1;
        deque<Soldier*>::iterator it = _soldiers.begin();

        for (; it != _soldiers.end(); ++it) {
            Soldier* soldier = *it;

            if (soldier->isSelected()) {
                soldier->setTarget(pos);// * offset);

                // Give each soldier a slight offset, this way they won't sit
                // on top of each other.
                offset += 0.05;
            }
        }
    }
}