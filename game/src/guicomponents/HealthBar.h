#ifndef HEALTHBAR_H_
#define HEALTHBAR_H_

#include <core/Composite.h>
#include <graphics/Graphics.h>
#include <utils/Util.h>

#include <sharedlib/gameobjects/GameObject.h>

class HealthBar : public phantom::Composite {
public:
    void update(const phantom::Time& time) {
        phantom::Graphics *g = &getGraphics();
        
        GameObject *o = static_cast<GameObject *>(_parent);
        Box3 _boundingBox = o->getBoundingBox();
        
        g->clear().beginPath().setFillStyle(Colors::MIDNIGHTBLUE);
        g->rect(0.0f, 0.0f, _boundingBox.size.x * (o->getHealth() / o->getTotalHealth()), 5.0f);
        g->fill();
    }
};

#endif // !HEALTHBAR_H_
