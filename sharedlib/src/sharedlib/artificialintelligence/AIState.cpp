#include "AIState.h"
#include "ArtificialIntelligence.h"
#include "../gameobjects/GameObject.h"

AIState::AIState() : ai(nullptr), _isEnabled(false) {

}

void AIState::construct() {
    _isEnabled = true;
}


void AIState::destruct() {
    _isEnabled = false;
}

MessageState AIState::handleMessage(AbstractMessage* message) {
    return IGNORED;
}

GameObject* AIState::getOwner() {
    return ai->getOwner();
}

bool AIState::isEnabled() {
    return _isEnabled;
}