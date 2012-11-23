#include "LightTank.h"
#include "../networking/NetworkRegistry.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/TankIdleState.h"
#include "../artificialintelligence/TankAttackState.h"
#include "../services/Services.h"

LightTank::LightTank() : isAttacking(false) {
    setType("Tank");

    _victim = nullptr;
    _boundingBox.size.x = 120.0f;
    _boundingBox.size.y = 120.0f;

    idleState = new TankIdleState();
    attackState = new TankAttackState(this);

    addComponent(new ArtificialIntelligence(this, idleState, attackState));

    setHealth(2000.0f);
}

LightTank::~LightTank() {
    delete idleState;
    delete attackState;
}

void LightTank::attack(GameObject *victim) {
    Box3& boundingbox = victim->getBoundingBox();

    _victim = victim;
    _victim->registerDestoryEvent(this);


    if(this->residence == GameObject::SERVER) {   
        Data data;
        data("victim") = victim->UID_network;
        isAttacking = true;
        Services::broadcast(this, new phantom::Message<Data>("Tank-shoot-start", data));
    }
}

void LightTank::shootAt(UID::Type uid) {
    if(NetworkRegistry::contains(uid)) {
        _victim = NetworkRegistry::get(uid);

        if(_victim == nullptr) {
            // We've already run a "contains" test, so this shouldn't be reached.
            // in the odd case it does happen, we'll silently ignore. It's no big
            // deal.
            return;
        }

        _victim->registerDestoryEvent(this);
    } else {
        // Probably out of sync with the network, not a big deal.
    }
}

MessageState LightTank::handleMessage(AbstractMessage *message) {
    if(message->isType("Tank-shoot-start")) {
        Data data = message->getPayload<Data>();
        shootAt(data("victim").toString());
        isAttacking = true;
        return CONSUMED;

    } else if(message->isType("Tank-shoot-stop")) {
        isAttacking = false;
        _victim = nullptr;
        return CONSUMED;
    }

    return GameObject::handleMessage(message);
}

void LightTank::fromData(Data &data) {
    GameObject::fromData(data);
    shootAt(data("victim").toString());
}

void LightTank::toData(Data& data) {
    GameObject::toData(data);

    if(_victim != nullptr) {
        data("victim") = _victim->UID_network;
    }
}