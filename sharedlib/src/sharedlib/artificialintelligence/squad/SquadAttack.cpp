#include "SquadAttack.h"
#include "sharedlib/gameobjects/LightWeapon.h"

SquadAttack::SquadAttack() : _victim(nullptr), _updateInterval(1) {

}

SquadAttack::~SquadAttack() {

}

void SquadAttack::setVictim(GameObject* gameobject) {
    _victim = gameobject;
}

void SquadAttack::construct() {
    AIState::construct();
}

void SquadAttack::handle(const phantom::PhantomTime& time) {
    if(_updateInterval.hasExpired(time)) {
        _updateInterval.restart();

        

        cout << "bar" << endl;
    }
}

MessageState SquadAttack::handleMessage(AbstractMessage* message) {
    if(message->isType("gameobject-destroyed")) {
        GameObject* victim = message->getPayload<GameObject*>();
        if(_victim == victim) {
            if(!isEnabled) {
                cout << "SquadAttack::handleMessage(): Good effort! Victim died without me attacking!" << endl;
            }

            return CONSUMED;
        }
    }

    return AIState::handleMessage(message);
}

void SquadAttack::destruct() {
    AIState::destruct();
    _victim = nullptr;
}