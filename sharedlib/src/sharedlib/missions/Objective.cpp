#include "Objective.h"
#include "../SharedException.h"

Objective::Objective(string title):_title(title) {

}

Objective::~Objective() {
}

std::vector<GameObject*> *Objective::getComposites() {
    return &_objects;
}