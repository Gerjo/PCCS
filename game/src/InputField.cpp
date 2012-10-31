#include "InputField.h"
#include <physics/Box3.h>
#include <core/Driver.h>
#include "components/KeyboardListener.h"

using namespace phantom;
using namespace std;

InputField::InputField(float x, float y, float width, float height, Color color) : _hasFocus(false), _text("Sometext because no keyboard hijack yet") {
    this->setX(x);
    this->setY(y);
    _color = color;
    this->setBoundingBox(Box3(x, y, width, height));
}

InputField::~InputField() {
}

void InputField::clicked(const MouseState& mouseState) {
    if(_keyboardListener->lock(this))
        _hasFocus = true;
}

void InputField::unclicked(const MouseState& mouseState) {
    _hasFocus = false;
    _keyboardListener->unlock(this);
}

string& InputField::text() {
    return _text;
}

void InputField::text(string value) {
    _text = value;
}

void InputField::update(const Time& time) {
    ClickableEntity::update(time);

    getGraphics().clear();
    
    Box3 *bb = &this->getBoundingBox();
    bb->size.x = (bb->size.x > bb->size.y / 2.5 * _text.length()) ? bb->size.x : bb->size.y / 2.5 * _text.length();
    getGraphics().beginPath().setFillStyle(_color).
        text(0.0f, 0.0f, bb->size.y / 2, "fonts/DejaVuSansMono-Bold.ttf", text()).
        rect(0.0f, 0.0f, bb->size.x, bb->size.y, false).
        fill().stroke();

    if(_hasFocus) {
        std::vector<char> *chars = getDriver()->getInput()->getKeyboardState()->changes();
        for(char c : *chars) {
            if(c == '\b') { // Action for backspace.
                if(_text.size() > 0) {
                    _text.erase(_text.end() - 1);
                }
            }
            else if(c == '\n') {
                unclicked(*getDriver()->getInput()->getMouseState());
            }
            else {
                _text.append(1, c);
            }
        }
    }
}