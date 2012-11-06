#include "Objective.h"
#include "../SharedException.h"

Objective::Objective() {
}

Objective::~Objective() {
}

std::vector<phantom::Composite*> *Objective::getComposites() {
    return &_composites;
}