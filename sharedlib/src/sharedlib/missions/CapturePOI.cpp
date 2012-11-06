#include "CapturePOI.h"
#include <core/Composite.h>
#include <core/PhantomGame.h>
#include <utils/Time.h>
CapturePOI::CapturePOI(phantom::Box3 poi, vector<LightSoldier*> eligibleSoldiers): _poi(poi), _eligible(eligibleSoldiers){
    ttl = -1;
    isCapturing = false;
}

CapturePOI::~CapturePOI(){
}


void CapturePOI::setConditions(){
    ttl = 90;
}
void CapturePOI::onCollision(Composite* entity){
    
    if(!isCapturing){
        setConditions();
    }
}
void CapturePOI::update(const Time& time){
    GameObject::update(time);
    if(ttl > 0){
        ttl -= time.getElapsed();
        if(ttl <= 0){
            
        }
    }
}

bool CapturePOI::conditionsMet(){
    if(ttl <= 0){
        return true;
    }
    return false;
}