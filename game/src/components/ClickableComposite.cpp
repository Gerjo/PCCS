#include <core/Driver.h>

#include "ClickableComposite.h"

using namespace phantom;

ClickableComposite::ClickableComposite()
{
}

ClickableComposite::~ClickableComposite()
{
}

void ClickableComposite::update(const Time& time) {
    Composite::update(time);

    MouseState* mouseState = getDriver()->getInput()->getMouseState();

    if(_boundingBox.contains(mouseState->getMousePosition()) && mouseState->isButtonDown(Buttons::LEFT_MOUSE)) {
        clicked(*mouseState);
    }
}