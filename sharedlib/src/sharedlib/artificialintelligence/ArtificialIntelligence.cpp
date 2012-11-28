#include "ArtificialIntelligence.h"

vector<GameObject*> ArtificialIntelligence::soldiers;

ArtificialIntelligence::ArtificialIntelligence(GameObject *parent) {
    if(parent == nullptr) {
        Console::log("Cannot add an AI behaviour to a non-gameobject.");
        return;
    }

    currentState = nullptr;
}

void ArtificialIntelligence::update(const phantom::PhantomTime& time) {
    Composite::update(time);

    // Do something that will detemine which state is currently active.
    if(currentState != nullptr && _parent != nullptr && static_cast<GameObject*>(_parent)->residence == GameObject::CLIENT)
        currentState->handle(time);
}

MessageState ArtificialIntelligence::handleMessage(AbstractMessage* message) {
    return Composite::handleMessage(message);
}

void ArtificialIntelligence::insertState(AIState *state) {
    state->ai = this;
    states.push_back(state);
}