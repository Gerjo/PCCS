#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_

#include <core/Composite.h>
#include <graphics/Graphics.h>
#include <phantom.h>

#include <sharedlib/gameobjects/GameObject.h>

class HealthBar : public phantom::Composite {
public:
    void update(const phantom::PhantomTime& time) {
        phantom::Graphics *g = &getGraphics();

        GameObject *o = static_cast<GameObject *>(_parent);
        Box3 _boundingBox = o->getBoundingBox();

        MouseState* mouseState = getDriver()->getInput()->getMouseState();
        g->clear();
        if(_boundingBox.intersects(mouseState->getPosition() + getDriver()->getActiveCameras()->at(0)->getPosition())) {
            g->beginPath().setFillStyle(Colors::BLACK);
            g->rect(0.0f, 0.0f, _boundingBox.size.x, 7.0f, false, 2.0f);
            g->fill().setFillStyle(Colors::RED);
            g->rect(2.0f, 2.0f, (_boundingBox.size.x * (o->getHealth() / o->getTotalHealth())) - 4.0f, 3.0f);
            g->fill();
        }

    }
};

#endif // !HEALTHBAR_H_
