#include "ArtificialIntelligence.h"

#include "../gameobjects/LightHelicopter.h"

vector<GameObject*> ArtificialIntelligence::soldiers;

ArtificialIntelligence::ArtificialIntelligence() {
}

void ArtificialIntelligence::update(const phantom::PhantomTime& time) {
    Composite::update(time);

    if(_parent != nullptr && static_cast<GameObject*>(_parent)->residence == GameObject::SERVER) {
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