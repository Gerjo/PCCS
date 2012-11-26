#ifndef ACTIONBAR_H_
#define ACTIONBAR_H_

#include <graphics/Graphics.h>
#include <input/Input.h>
#include <core/Composite.h>

class ActionBar : public phantom::Composite{
public:
    bool visible;

    virtual void update(const phantom::PhantomTime& time) {
        getGraphics().clear();
        if(visible) {
            float loc[] = { 579.5f, 917.0f };
            phantom::MouseState *mousestate = getDriver()->getInput()->getMouseState();
            phantom::Vector3 mousepos = mousestate->getPosition();

            getGraphics().beginPath().setFillStyle(phantom::Colors::WHITE)
                .image("images/hud menu/menu bg.png", loc[0], loc[1], 761.0f, 163.0f)
                .image("images/hud menu/menu 1.png", loc[0] + 10.0f, loc[1] + 10.0f, 209.0f, 68.0f)
                .image("images/hud menu/menu 2.png", loc[0] + 225.0f, loc[1] + 10.0f, 209.0f, 68.0f)
                .image("images/hud menu/menu 3.png", loc[0] + 10.0f, loc[1] + 85.0f, 209.0f, 68.0f)
                .image("images/hud menu/menu 4.png", loc[0] + 225.0f, loc[1] + 85.0f, 209.0f, 68.0f)
                .image("images/hud menu/menu inventory.png", loc[0] + 450.0f, loc[1] + 10.0f, 296.0f, 144.0f)
                .stroke();

            // Very huge hack, I'm not really sure how we should handle who gets the mouse. Usually there is a Z-axis we can query, but in this case, we don't
            // have that inserted yet.
            if(mousepos.x > 579.5f && mousepos.x < 1340.5f && mousepos.y > 917.0f && mousepos.y < 1080 && mousestate->isButtonDown(phantom::Buttons::LEFT_MOUSE)) {
                mousestate->handleEvent(phantom::Buttons::LEFT_MOUSE, 0);
            }
        }
    }
};

#endif