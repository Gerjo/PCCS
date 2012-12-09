#include "ArtificialIntelligence.h"

#include "../gameobjects/LightHelicopter.h"

vector<GameObject*> ArtificialIntelligence::soldiers;


ArtificialIntelligence::ArtificialIntelligence() {

}

void ArtificialIntelligence::update(const phantom::PhantomTime& time) {
    Composite::update(time);

    GameObject::ResidenceState runstate = static_cast<GameObject*>(_parent)->residence;

    if(_parent != nullptr && (runstate == runat || runat == GameObject::BOTH)) {

        for(auto iterator = states.begin(); iterator != states.end(); ++iterator) {
            if((*iterator)->isEnabled)
                (*iterator)->handle(time);
        }
    }
}

MessageState ArtificialIntelligence::handleMessage(AbstractMessage* message) {
    MessageState state = Composite::handleMessage(message);

    if(state == MessageState::CONSUMED) {
        return state;
    }

    // States are not a composite (to save memory?) so we must manually broadcast.
    for (AIState* aistate : states) {
        state = aistate->handleMessage(message);
        if (state == MessageState::CONSUMED) {
            return state;
        }
    }

    return state;
}

void ArtificialIntelligence::insertState(AIState *state) {
    state->ai = this;
    states.push_back(state);
}

void ArtificialIntelligence::disableAll(void) {
    for(AIState* state : states) {
        state->destruct();
    }
}