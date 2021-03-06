#include "ObjDestroy.h"

ObjDestroy::ObjDestroy(string title): Objective(title), _objectCounter(0) {
    
}

void ObjDestroy::setConditions(){
    
}
ObjDestroy::~ObjDestroy() {
}

void ObjDestroy::addObject(GameObject* gob){
    if(!wasMore)
        wasMore = true;

    _objects.push_back(gob);
    _objectCounter++;
}
void ObjDestroy::addComponent(Composite* composite){
    Objective::addComponent(composite);
    if(GameObject* gob = dynamic_cast<GameObject*>(composite)){
        addObject(gob);
    }
}

bool ObjDestroy::conditionsMet() {
    std::vector<GameObject*>::iterator gobs;
    int c = 0;
    for(gobs = _objects.begin(); gobs != _objects.end(); ++gobs) {
        GameObject *gob = static_cast<GameObject*>(*gobs);
        c += gob->isDestroyed();
    }
    if(c == _objectCounter){
        Console::log("Objective complete: " + _title);
        return true;
    }
    else if(forcedComplete) {
        return true;
    }
    else
        return false;
}