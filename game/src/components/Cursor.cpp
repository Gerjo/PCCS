#include "Cursor.h"

Cursor::Cursor() : _doRedraw(true), currentCursor(CURNORMAL), _rotation(1) {
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

    if(currentCursor == CURNORMAL) {
        getGraphics()
            .clear()
            .beginPath()
            .setFillStyle(Colors::WHITE)
            .image("images/cursors/mouse3.png", 0, 0, 49, 65).stroke();
        ;
    }
    else if(currentCursor == CURATTACK) {
        stringstream s;
        s << _rotation;
        getGraphics().clear().beginPath().setFillStyle(Colors::WHITE).image("images/cursors/fire" + s.str() + ".png", -42, -42, 85, 85);
        _rotation++;
        if(_rotation > 4)
            _rotation = 1;
        _doRedraw = true;

        if(_tooltip.empty())
            currentCursor = CURNORMAL;
    }

    if(!_tooltip.empty()) {
        getGraphics().text(50.0f, 70.0f, 18, "fonts/waree.ttf", _tooltip);
    }

    getGraphics().stroke();

}

void Cursor::redraw() {
    _doRedraw = true;
}
void Cursor::setTooltip(string tooltip) {
    _doRedraw = true;
    _tooltip  = tooltip;
}
