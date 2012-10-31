#include "InputField.h"
#include <physics/Box3.h>

using namespace phantom;
using namespace std;

InputField::InputField(float x, float y, float width, float height, Color color) : _hasFocus(false), _text("Sometext because no keyboard hijack yet") {
    this->setX(x);
    this->setY(y);
    this->setBoundingBox(Box3(x, y, width, height));
}

InputField::~InputField() {
}

void InputField::clicked(const MouseState& mouseState) {
    _hasFocus = true;
}

void InputField::unclicked(const MouseState& mouseState) {
    _hasFocus = false;
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
    getGraphics().beginPath().setFillStyle(Colors::WHITE).
        text(0.0f, 0.0f, bb->size.y / 2, "fonts/DejaVuSansMono-Bold.ttf", text()).
        rect(0.0f, 0.0f, bb->size.x, bb->size.y, false).
        fill().stroke();

    if(_hasFocus) {
        //HIJACK ALL THE KEYBOARD AND FILL IN THE DATAZ!
    }
}