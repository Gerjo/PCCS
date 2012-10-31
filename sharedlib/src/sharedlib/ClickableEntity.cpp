#include <core/Driver.h>
#include <core/Camera.h>

#include "ClickableEntity.h"
#include "SharedException.h"

using namespace phantom;

void ClickableEntity::update(const Time& time) {
    Entity::update(time);

    MouseState* mouseState = getDriver()->getInput()->getMouseState();
    Vector3 &mousePosition = mouseState->getMousePosition();
    Vector3 &camPosition = getDriver()->getActiveCamera()->getPosition();

    if(_boundingBox.contains(mousePosition + camPosition) && mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
        clicked(*mouseState);
    } else if(mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
        unclicked(*mouseState);
    }
}