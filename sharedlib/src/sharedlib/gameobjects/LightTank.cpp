#include "LightTank.h"
#include "../networking/NetworkRegistry.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/TankIdleState.h"
#include "../artificialintelligence/TankAttackState.h"
#include "../services/Services.h"

LightTank::LightTank() : EnemyMixin(this), isAttacking(false) {
    setType("Tank");

    _victim = nullptr;
    _boundingBox.size.x = 120.0f;
    _boundingBox.size.y = 120.0f;

    ArtificialIntelligence *ai = new ArtificialIntelligence(this);
    idleState = new TankIdleState(this);
    attackState = new TankAttackState(this);
    ai->insertState(idleState);
    ai->insertState(attackState);
    ai->setActive<TankIdleState>();
    addComponent(ai);

    // Automaticly bound to this->mover.
    addComponent(new Mover());

    setHealth(2000.0f);
}

LightTank::~LightTank() {
    delete idleState;
    delete attackState;
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
    if(!mover->isStopped())
        return;

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
        return CONSUMED;

    } else if(message->isType("Tank-shoot-stop")) {
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