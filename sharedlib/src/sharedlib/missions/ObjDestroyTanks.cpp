#include "ObjDestroyTanks.h"

ObjDestroyTanks::ObjDestroyTanks(string title): Objective(title) {
    
}

void ObjDestroyTanks::setConditions(){
    
}
ObjDestroyTanks::~ObjDestroyTanks() {
}

void ObjDestroyTanks::addObject(GameObject* gob){
    _objects.push_back(gob);
}

bool ObjDestroyTanks::conditionsMet() {
    std::vector<GameObject*>::iterator gobs;
    int c = 0;
    for(gobs = _objects.begin(); gobs != _objects.end(); ++gobs) {
        GameObject *gob = static_cast<GameObject*>(*gobs);
        c += gob->isDestroyed();
    }
    if(c == 5){
        cout << " Objective complete!" << endl;
        return true;
    }else
        return false;
}