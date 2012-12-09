#include "SquadAttack.h"

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

void SquadAttack::destruct() {
    AIState::destruct();
    _victim = nullptr;
}