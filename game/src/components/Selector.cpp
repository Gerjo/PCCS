#include "Selector.h"

Selector::Selector() {

}

Selector::~Selector() {

}

void Selector::update(const float& elapsed) {

}

MessageState Selector::handleMessage(AbstractMessage* message) {
    if(message->isType("selector-register")) {
        HeavySoldier* soldier = message->getPayload<HeavySoldier*>();
        _soldiers.push_back(soldier);
    }
}
