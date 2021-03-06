#include "ArtificialIntelligence.h"

vector<GameObject*> ArtificialIntelligence::soldiers;

ArtificialIntelligence::ArtificialIntelligence() {

}

vector<GameObject*> *ArtificialIntelligence::getSoldiers() {
    return &soldiers;
}

void ArtificialIntelligence::update(const phantom::PhantomTime& time) {
    Composite::update(time);

    GameObject::ResidenceState runstate = static_cast<GameObject*>(_parent)->residence;

    if(_parent != nullptr && (runstate == runat || runat == GameObject::BOTH)) {
        for(AIState* state : states) {
            if(state->isEnabled()) {
                state->update(time);
            }
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