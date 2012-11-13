#ifndef CAPTURE_POINT_OF_INTEREST_H
#define CAPTURE_POINT_OF_INTEREST_H

#include "Objective.h"
#include "../gameobjects/LightSoldier.h"
#include <physics/Box3.h>
#include <phantom.h>

using phantom::Timer;

class LIBEXPORT ObjCapture : public Objective, public GameObject{
public:
    ObjCapture(phantom::Box3 poi, string title);
    ~ObjCapture();
    void update(const Time& time);

    virtual void onCollision(Composite* entity);
    virtual void setConditions();
    virtual bool conditionsMet();
private:
    phantom::Box3 _poi;
    Timer timer;
    float ttl;
    bool isCapturing;
};

#endif /* CAPTURE_POINT_OF_INTEREST_H */