#include "Objective.h"
#include "../SharedException.h"

Objective::Objective(string title):_title(title), wasMore(false), forcedComplete(false) {

}

Objective::~Objective() {
}
string Objective::getTitle(){
    return _title;
}

std::vector<GameObject*> *Objective::getComposites() {
    return &_objects;
}