#ifndef CAPTURE_POINT_OF_INTEREST_H
#define CAPTURE_POINT_OF_INTEREST_H

#include "Objective.h"
#include "../gameobjects/LightSoldier.h"
#include <physics/Box3.h>
#include "../Timer.h"

class LIBEXPORT CapturePOI : public Objective, public GameObject{
public:
    CapturePOI(phantom::Box3 poi, string title);
    ~CapturePOI();
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