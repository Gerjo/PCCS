#include "ArtificialIntelligence.h"

vector<GameObject*> ArtificialIntelligence::soldiers;

ArtificialIntelligence::ArtificialIntelligence(AIState *idle, AIState *attack, AIState *defending, AIState *fleeing) : currentState(STATEIDLE), states(4) {
    parent = dynamic_cast<GameObject*>(getParent());

    if(parent == nullptr) {
        Console::log("Cannot add an AI behaviour to a non-gameobject.");
        return;
    }

    setStates(idle, attack, defending, fleeing);
    setActive(STATEATTACKING);
}

void ArtificialIntelligence::setStates(AIState *idle, AIState *attack, AIState *defending, AIState *fleeing) {
    clearStates();

    idle->object = parent;
    states.push_back(idle);

    attack->object = parent;
    states.push_back(attack);

    defending->object = parent;
    states.push_back(defending);

    fleeing->object = parent;
    states.push_back(fleeing);
}

void ArtificialIntelligence::update(const phantom::Time& time) {
    Composite::update(time);

    // Do something that will detemine which state is currently active.

    if(states[currentState] != nullptr) states[currentState]->handle(time);
}

MessageState ArtificialIntelligence::handleMessage(AbstractMessage* message) {
    return Composite::handleMessage(message);
}


void ArtificialIntelligence::setActive(STATE state) {
    if(states[currentState] != nullptr) states[currentState]->destruct();
    currentState = state;
    if(states[currentState] != nullptr) states[currentState]->construct();
}

void ArtificialIntelligence::clearStates() {
    for(AIState *state : states) {
        if(state != nullptr) delete state;
    }
    states.clear();
}