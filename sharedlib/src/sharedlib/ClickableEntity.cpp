#include <core/Driver.h>
#include "ClickableEntity.h"
#include "SharedException.h"

using namespace phantom;

ClickableEntity::ClickableEntity(Camera *camera) {
    _camera = camera;
}

void ClickableEntity::update(const Time& time) {
    Entity::update(time);

    MouseState* mouseState = getDriver()->getInput()->getMouseState();

    if(_boundingBox.contains(mouseState->getMousePosition() + _camera->getPosition()) && mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
        clicked(*mouseState);
    } else if(mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
        unclicked(*mouseState);
    }
}