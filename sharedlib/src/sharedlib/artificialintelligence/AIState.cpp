#include "AIState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/GameObject.h"

AIState::AIState() : ai(nullptr), isEnabled(false) {

}

void AIState::construct() {
    isEnabled = true;
}


void AIState::destruct() {
    isEnabled = false;
}

MessageState AIState::handleMessage(AbstractMessage* message) {
    return IGNORED;
}

GameObject* AIState::getOwner() {
    return ai->getOwner();
}
