#include "EnemyMixin.h"
#include "../services/Services.h"
#include "../networking/NetworkRegistry.h"

EnemyMixin::EnemyMixin(GameObject *me) : _isAttacking(false), _me(me), _victim(nullptr) {
}

void EnemyMixin::loop() { 
    if(_isAttacking) {

    }
}

void EnemyMixin::attack(GameObject *victim) {
    Box3& boundingbox = victim->getBoundingBox();

    _victim = victim;
    //_victim->registerDestoryEvent(_me);

    if(_me->residence == GameObject::SERVER && _isAttacking == false) {
        Data data;
        _isAttacking = true;
        data("victim") = victim->UID_network;
        Services::broadcast(_me, new phantom::Message<Data>(_me->getType() + "-shoot-start", data));
    }
}

void EnemyMixin::shootAt(UID::Type uid) {
    if(NetworkRegistry::contains(uid)) {
        _victim = NetworkRegistry::get(uid);

        if(_victim == nullptr) {
            // We've already run a "contains" test, so this shouldn't be reached.
            // in the odd case it does happen, we'll silently ignore. It's no big
            // deal.
            return;
        }

        _victim->registerDestoryEvent(_me);
    } else {
        // Probably out of sync with the network, not a big deal.
    }
}

void EnemyMixin::stopShooting() {
    if(_victim) {
        _isAttacking = false;
        _victim = nullptr;
        if(_me->residence == GameObject::SERVER)
            Services::broadcast(_me, new phantom::Message<Data>(_me->getType() + "-shoot-stop", Data()));
    }
}

bool EnemyMixin::hasVictim() {
    return (_victim != nullptr);
}

bool EnemyMixin::isAttacking() {
    return _isAttacking;
}

GameObject *EnemyMixin::getVictim() {
    return _victim;
}

