#include "InputField.h"
#include <physics/Box3.h>
#include <core/Driver.h>
#include "../components/Clicktor.h"

using namespace phantom;
using namespace std;

InputField::InputField(Camera *camera, float x, float y, float width, float height, Color color) : _hasFocus(false), _text("Sometext because no keyboard hijack yet") {
    this->setX(x);
    this->setY(y);
    _color = color;
    Clicktor* click = new Clicktor();
    click->setCamera(camera);
    addComponent(click);

    this->setBoundingBox(Box3(x, y, width, height));
}

InputField::~InputField() {

}

void InputField::onClick(MouseState* mouseState) {
    if(KeyboardListener::lock(this))
        _hasFocus = true;
}

void InputField::onUnClicked(MouseState* mouseState) {
    _hasFocus = false;
    KeyboardListener::unlock(this);
}

string& InputField::text() {
    return _text;
}

void InputField::text(string value) {
    _text = value;
}

void InputField::update(const Time& time) {
    GameObject::update(time);

    getGraphics().clear();

    Box3 *bb = &this->getBoundingBox();
    bb->size.x = (bb->size.x > bb->size.y / 2.5f * _text.length()) ? bb->size.x : bb->size.y / 2.5f * _text.length();
    getGraphics().beginPath().setFillStyle(_color).
        text(0.0f, 0.0f, static_cast<int>(bb->size.y / 2), "fonts/DejaVuSansMono-Bold.ttf", text()).
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
            else if(c == '\n' || c == '\r') {
                onUnClicked(getDriver()->getInput()->getMouseState());
            }
            else {
                _text.append(1, c);
            }
        }
    }
}