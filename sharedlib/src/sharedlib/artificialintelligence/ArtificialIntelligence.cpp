#include "ArtificialIntelligence.h"

vector<GameObject*> ArtificialIntelligence::soldiers;

ArtificialIntelligence::ArtificialIntelligence(GameObject *parent) : runat(GameObject::SERVER) {
    if(parent == nullptr) {
        Console::log("Cannot add an AI behaviour to a non-gameobject.");
        return;
    }
}

void ArtificialIntelligence::update(const phantom::PhantomTime& time) {
    Composite::update(time);

    if(_parent != nullptr && static_cast<GameObject*>(_parent)->residence == runat) {

        for(auto iterator = states.begin(); iterator != states.end(); ++iterator) {
            if((*iterator)->isEnabled)
                (*iterator)->handle(time);
        }
    }
}

MessageState ArtificialIntelligence::handleMessage(AbstractMessage* message) {
    return Composite::handleMessage(message);
}

void ArtificialIntelligence::insertState(AIState *state) {
    state->ai = this;
    states.push_back(state);
}