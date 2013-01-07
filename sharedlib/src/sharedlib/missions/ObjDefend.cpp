#include "ObjDefend.h"

ObjDefend::ObjDefend(GameObject* target, string title): Objective(title), _target(target), timer(5){
    ttl = 60;
    setType(title);
    _isDefending = false;
}
ObjDefend::~ObjDefend(){

}
void ObjDefend::setConditions(){
    ttl = 60;
    _isDefending = true;
    timer.setDelay(ttl);
    timer.restart();
}
bool ObjDefend::conditionsMet(){
    if(_target->isDestroyed()) return true;
    if(timer.hasExpired()) return true;

    return false;
}

void ObjDefend::update(const PhantomTime& time){
    Objective::update(time);
}