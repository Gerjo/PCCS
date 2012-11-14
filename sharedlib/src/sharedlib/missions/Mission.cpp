#include "Mission.h"
#include <core/Console.h>
Mission::Mission(const std::string& title) {
    //Generate some mission at the moment.
    setType("Mission");

    std::function<void()> function = [this] () {
        // Will cause a memory leak since the components are not being deleted.
        _objectives.clear();
    };
    Console::mapCommand("complete " + title, function);
}

Mission::~Mission() {
}

void Mission::addObjective(Objective *objectiveID) {
    _objectives.push_back(objectiveID);
    Console::log("New objective: " + objectiveID->getTitle());
}

void Mission::toData(Data& data){
    GameObject::toData(data);
}

void Mission::fromData(Data& data){
    GameObject::fromData(data);

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
void Mission::update(const Time& time){
    GameObject::update(time);
    checkIfCompleted();
}

void Mission::checkIfCompleted() {
    for(std::vector<Objective*>::iterator o = _objectives.begin(); o != _objectives.end();) {
        if((*o)->wasMore){
            if((*o)->conditionsMet()) {
                (*o)->destroy();
                //delete *o;
                *o = 0;
                o = _objectives.erase(o);
            }else{
                ++o;
            }
        }else{
            ++o;
        }
    }
}

bool Mission::missionComplete() {
    if(_objectives.size() == 0) {
        return true;
    }
    else return false;
}
