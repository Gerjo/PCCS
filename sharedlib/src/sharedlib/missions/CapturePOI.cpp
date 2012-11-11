#include "CapturePOI.h"
#include <core/Composite.h>
#include <core/PhantomGame.h>
#include <utils/Time.h>

CapturePOI::CapturePOI(phantom::Box3 poi, string title): Objective(title), _poi(poi), timer(5){
    ttl = -1;
    isCapturing = false;
    _boundingBox = _poi;
    setType(title);
}

CapturePOI::~CapturePOI(){
}


void CapturePOI::setConditions(){
    ttl = 10;
    isCapturing = true;
}
void CapturePOI::onCollision(Composite* entity){
    if(entity->isType("Soldier")){
        if(!isCapturing){
            cout << "capturing!" << endl;
            setConditions();
        }
    }
}
void CapturePOI::update(const Time& time){
    GameObject::update(time);

    getGraphics()
        .clear()
        .beginPath()
        .setFillStyle(Colors::WHITE)
        .rect(_poi)
        .fill()
        .stroke()
        ;

    if(ttl >= 0){
        ttl -= time.getElapsed();
    }
}

bool CapturePOI::conditionsMet(){
    if(ttl <= 0 && isCapturing){
        cout << "objective complete" << endl;
        return true;
    }
    return false;
}