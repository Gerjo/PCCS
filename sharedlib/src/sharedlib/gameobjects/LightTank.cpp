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

    // Automaticly bound to this->mover.
    addComponent(new Mover());

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

void LightTank::stopShooting() {
    isAttacking = false;
    if(this->residence == GameObject::SERVER)
        Services::broadcast(this, new phantom::Message<Data>("Tank-shoot-stop", Data()));
}

Pathfinding::Route LightTank::seekRoute(Vector3 location) {
    Pathfinding* pathfinding = static_cast<BSPTree*>(_layer)->pathfinding;

    Pathfinding::Route _path = pathfinding->getPath(this, location);

    if(_path.empty()) {
        Console::log("LightTank.cpp: No route found to destination.");
    }

    mover->moveTo(&_path);

    return _path;
}

void LightTank::drive(Vector3 location) {
    Pathfinding::Route _path = seekRoute(location);

    stringstream ss;

    if(_path.empty()) {
        ss << "Tank: Cannot find route to destination.";
    } else {
        ss << "Tank: Driving to location (" << _path.size() << " waypoints).";
    }

    Console::log(ss.str());

    Data data;
    data("to-x") = location.x;
    data("to-y") = location.y;
    data("x")    = _position.x;
    data("y")    = _position.y;

    _direction = location - _position;
    _direction.normalize();

    if(this->residence == GameObject::SERVER) Services::broadcast(this, new phantom::Message<Data>("Tank-walk-to", data));
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
    if(message->isType("Tank-walk-to")) {
        Data data = message->getPayload<Data>();

        // Our amazing position integration:
        _position.x = data("x");
        _position.y = data("y");

        seekRoute(Vector3(data("to-x"), data("to-y"), 0.0f));

        return CONSUMED;

    } else if(message->isType("Tank-shoot-start")) {
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