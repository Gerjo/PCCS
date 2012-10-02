#include "Selector.h"

#include "gameobjects/Soldier.h"

Selector::Selector() :
    _startpoint(0, 0, 0),
    _endpoint(0, 0, 0),
    _hasStartpoint(false)
{

}

void Selector::draw(void) {
    getGraphics().clear();

    // Conditionally show the selection.
    if(_hasStartpoint) {
        getGraphics()
            .beginPath()
            .setFillStyle(Color::HOTPINK)
            .rect(_startpoint.x(), _startpoint.y(), _endpoint.x() - _startpoint.x(), _endpoint.y() - _startpoint.y())
            .beginPath();
    }
}

void Selector::update(const float& elapsed) {
    bool doRedraw    = false;
    MouseState* mouse = InputState::getMe()->getMouseState();

    // Selection of units:
    if(mouse->isButtonDown(MouseState::BUTTON_LEFT)) {
        if(!_hasStartpoint) {
            _startpoint = mouse->getMousePosition();
            _hasStartpoint = true;
            start();
        } else {
            // The user is "dragging" his mouse.
            if(_endpoint != mouse->getMousePosition()) {
                _endpoint = mouse->getMousePosition();
                doRedraw = true;
            }
        }

    } else {
        if(_hasStartpoint) {
            _hasStartpoint = false;
            doRedraw = true;

            finalize();
        }
    }


    if(mouse->isButtonDown(MouseState::BUTTON_RIGHT)) {
        // if(_hasStartPoint) {
            _hasStartpoint = false;
            doRedraw = true;

            cancel();
        //}
    }

    if(doRedraw) {
        draw();
    }
}

void Selector::addSoldier(Soldier* soldier) {
    _soldiers.push_back(soldier);
}

void Selector::start(void) {
    deque<Soldier*>::iterator it = _soldiers.begin();

    for(; it != _soldiers.end(); ++it) {
        Soldier* soldier = *it;
        soldier->setSelected(true);
    }

    cout << "start" << endl;
}

void Selector::finalize(void) {
    cout << "finalize" << endl;
}

void Selector::cancel(void) {
    cout << "cancel" << endl;
    
    deque<Soldier*>::iterator it = _soldiers.begin();

    for(; it != _soldiers.end(); ++it) {
        Soldier* soldier = *it;
        soldier->setSelected(false);
    }
}