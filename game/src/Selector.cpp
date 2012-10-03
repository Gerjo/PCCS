#include "Selector.h"

#include "gameobjects/Soldier.h"

Selector::Selector() :
_startpoint(0, 0, 0),
_endpoint(0, 0, 0),
_hasStartpoint(false),
_hasSelection(false) {

}

void Selector::draw(void) {
    getGraphics().clear();

    // Conditionally show the selection.
    if (_hasStartpoint) {
        getGraphics()
                .beginPath()
                .setFillStyle(Colors::HOTPINK)
                .rect(_startpoint.x(), _startpoint.y(), _endpoint.x() - _startpoint.x(), _endpoint.y() - _startpoint.y())
                .stroke();
    }
}

void Selector::update(const float& elapsed) {
    bool doRedraw = false;
    MouseState* mouse = InputState::getMe()->getMouseState();

    // Selection of units:
    if (mouse->isButtonDown(Buttons::LEFT_MOUSE)) {
        if (!_hasStartpoint) {
            _startpoint = mouse->getMousePosition();
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
            // the treshold. This is usefull for people who quickly click whilst
            // the mouse is still moving. You want this click to be a click, and
            // not the start of a new selection;
            const float threshold = 2.0f;

            if (abs(_endpoint.x() - _startpoint.x()) > threshold &&
                    abs(_endpoint.y() - _startpoint.y()) > threshold) {

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

    Vector2f upperbound(
            max(_startpoint.x(), _endpoint.x()),
            max(_startpoint.y(), _endpoint.y())
            );

    Vector2f lowerbound(
            min(_startpoint.x(), _endpoint.x()),
            min(_startpoint.y(), _endpoint.y())
            );

    deque<Soldier*>::iterator it = _soldiers.begin();

    for (; it != _soldiers.end(); ++it) {
        Soldier* soldier = *it;
        const Vector3f& pos = soldier->getPosition();
        bool isSelected = false;


        if (pos.x() > lowerbound.x() && pos.x() < upperbound.x()) {
            if (pos.y() > lowerbound.y() && pos.y() < upperbound.y()) {
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
        MouseState* mouse = InputState::getMe()->getMouseState();
        const Vector3f& pos = mouse->getMousePosition();
        float offset = 1;
        deque<Soldier*>::iterator it = _soldiers.begin();

        for (; it != _soldiers.end(); ++it) {
            Soldier* soldier = *it;

            if (soldier->isSelected()) {
                soldier->setTarget(pos * offset);
                
                // Give each soldier a slight offset, this way they won't sit
                // on top of each other.
                offset += 0.05;
            }
        }
    }
}