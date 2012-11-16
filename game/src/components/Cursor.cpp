#include "Cursor.h"

Cursor::Cursor() : _doRedraw(true) {
    setType("Cursor");
}

void Cursor::update(const Time& time) {
    Entity::update(time);

    MouseState* mouseState = getPhantomGame()->getDriver()->getInput()->getMouseState();
    Vector3 position = mouseState->getPosition();

    if(!getPhantomGame()->getDriver()->getActiveCameras()->empty())
        position += getPhantomGame()->getDriver()->getActiveCameras()->at(0)->getPosition();

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
            .image("images/cursors/mouse3.png", 0, 0, 49, 65)
            ;

    if(!_tooltip.empty()) {
        getGraphics().text(50.0f, 70.0f, 18, "fonts/waree.ttf", _tooltip);
    }

    getGraphics().stroke();
}

void Cursor::setTooltip(string tooltip) {
    _doRedraw = true;
    _tooltip  = tooltip;
}
