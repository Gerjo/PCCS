#include "Cursor.h"

Cursor::Cursor() : _doRedraw(true) {

}

void Cursor::update(const float& elapsed) {
    Entity::update(elapsed);

    MouseState* mouseState = getGame()->getDriver()->getInput()->getMouseState();
    Vector3 position = mouseState->getMousePosition();

    setPosition(position);

    if(_doRedraw) {
        draw();
    }
}

void Cursor::draw(void) {
    _doRedraw = false;

    getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::WHITE)
            //.rect(0, 0, 1, 1)
            ;

    if(!_tooltip.empty()) {
        getGraphics().text(10, 30, GLUT_BITMAP_HELVETICA_10, &_tooltip);
    }

    getGraphics().stroke();
}

void Cursor::setTooltip(string tooltip) {
    _doRedraw = true;
    _tooltip  = tooltip;
}
