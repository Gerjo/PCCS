#include <core/Driver.h>

#include "ClickableEntity.h"

using namespace phantom;

ClickableEntity::ClickableEntity()
{
}

ClickableEntity::~ClickableEntity()
{
}

void ClickableEntity::clicked(const MouseState& mouseState) {
    cout << "Clicked component with type: " << this->toString();
}

void ClickableEntity::update(const Time& time) {
    Entity::update(time);

    MouseState* mouseState = getDriver()->getInput()->getMouseState();

    if(_boundingBox.contains(mouseState->getMousePosition()) && mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
        clicked(*mouseState);
    }
}