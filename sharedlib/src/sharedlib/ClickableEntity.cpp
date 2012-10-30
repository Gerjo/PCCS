#include <core/Driver.h>

#include "ClickableEntity.h"
#include "SharedException.h"

using namespace phantom;

void ClickableEntity::update(const Time& time) {
    Entity::update(time);

    MouseState* mouseState = getDriver()->getInput()->getMouseState();

    if(_boundingBox.contains(mouseState->getMousePosition()) && mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
        clicked(*mouseState);
    } else if(mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
        unclicked(*mouseState);
    }
}