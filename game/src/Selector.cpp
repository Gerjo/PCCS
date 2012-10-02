#include "Selector.h"

Selector::Selector() :
    _start(0, 0, 0),
    _end(0, 0, 0)
{

    _hasStartPoint = false;

}

void Selector::draw(void) {
    getGraphics().clear();

    // Conditionally show the selection.
    if(_hasStartPoint) {
        getGraphics()
            .beginPath()
            .setFillStyle(Color::HOTPINK)
            .rect(_start.x(), _start.y(), _end.x() - _start.x(), _end.y() - _start.y())
            .beginPath();
    }
}

void Selector::update(const float& elapsed) {
    bool doRedraw    = false;
    MouseState* mouse = InputState::getMe()->getMouseState();

    // Selection of units:
    if(mouse->isButtonDown(MouseState::BUTTON_LEFT)) {
        if(!_hasStartPoint) {
            cout << "init click " << endl;
            _start = mouse->getMousePosition();

            _hasStartPoint = true;
        } else {
            // The user is "dragging" his mouse.
            if(_end != mouse->getMousePosition()) {
                _end = mouse->getMousePosition();
                doRedraw = true;
            }
        }

    } else {
        if(_hasStartPoint) {
            cout << "Finalizing selection. Hiding selection tool." << endl;
            _hasStartPoint = false;
            doRedraw = true;
        }
    }

    if(doRedraw) {
        draw();
    }
}

