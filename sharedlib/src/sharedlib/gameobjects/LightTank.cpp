#include "LightTank.h"
#include "../networking/NetworkRegistry.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/TankIdleState.h"
#include "../artificialintelligence/TankAttackState.h"

LightTank::LightTank() : isAttacking(false) {
    setType("Tank");

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

    return IGNORED;
}

void LightTank::fromData(Data &data) {
    GameObject::fromData(data);
    shootAt(data("victim").toString());
}