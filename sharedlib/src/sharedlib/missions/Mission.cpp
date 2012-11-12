#include "Mission.h"

Mission::Mission() {
    //Generate some mission at the moment.
}

Mission::~Mission() {
}

void Mission::addObjective(Objective *objectiveID) {
    _objectives.push_back(objectiveID);
}

void Mission::removeObjective(Objective *objectiveID) {
    std::vector<Objective*>::iterator obj;
    for(obj = _objectives.begin(); obj != _objectives.end(); ++obj) {
        if(*obj == objectiveID) {
            _objectives.erase(obj);
            return;
        }
    }
}

void Mission::checkIfCompleted() {
    for(std::vector<Objective*>::iterator o = _objectives.begin(); o != _objectives.end();) {
        if((*o)->conditionsMet()) {
            delete *o;
            *o = 0;
            o = _objectives.erase(o);
        }
        else
            ++o;
    }
}

bool Mission::missionComplete() {
    if(_objectives.size() == 0) {
        return true;
    }
    else return false;
}
