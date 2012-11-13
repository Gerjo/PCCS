#include "ObjDestroy.h"

ObjDestroy::ObjDestroy(string title): Objective(title), _objectCounter(0) {
    
}

void ObjDestroy::setConditions(){
    
}
ObjDestroy::~ObjDestroy() {
}

void ObjDestroy::addObject(GameObject* gob){
    _objects.push_back(gob);
    _objectCounter++;
}

bool ObjDestroy::conditionsMet() {
    std::vector<GameObject*>::iterator gobs;
    int c = 0;
    for(gobs = _objects.begin(); gobs != _objects.end(); ++gobs) {
        GameObject *gob = static_cast<GameObject*>(*gobs);
        c += gob->isDestroyed();
    }
    if(c == _objectCounter){
        cout << " Objective complete!" << endl;
        return true;
    }else
        return false;
}