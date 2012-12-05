#include "LightTank.h"
#include "../networking/NetworkRegistry.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/TankIdleState.h"
#include "../artificialintelligence/TankAttackState.h"
#include "../artificialintelligence/TankDefendState.h"
#include "../services/Services.h"

LightTank::LightTank() : EnemyMixin(this), isAttacking(false) {
    setType("Tank");

    _boundingBox.size.x = 120.0f;
    _boundingBox.size.y = 120.0f;
    _killList.push_back("Soldier");

    ArtificialIntelligence *ai = new ArtificialIntelligence(this);
    idleState = new TankIdleState(this);
    attackState = new TankAttackState(this);
    defendState = new TankDefendState(this);
    ai->insertState(idleState);
    ai->insertState(attackState);
    ai->insertState(defendState);
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

    mover->moveTo(_path);

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

    if(this->residence == GameObject::SERVER) {
        string broadcastType = getType() + "-walk-to";
        Services::broadcast(this, new phantom::Message<Data>(broadcastType, data));
    }
}

MessageState LightTank::handleMessage(AbstractMessage *message) {
    if(message->isType(getType() + "-walk-to")) {
        Data data = message->getPayload<Data>();

        // Our amazing position integration:
        _position.x = data("x");
        _position.y = data("y");

        seekRoute(Vector3(data("to-x"), data("to-y"), 0.0f));

        return CONSUMED;

    } else if(message->isType(getType() + "-shoot-start")) {
        Data data = message->getPayload<Data>();
        shootAt(data("victim").toString());
        return CONSUMED;

    } else if(message->isType(getType() + "-shoot-stop")) {
        stopShooting();
        return CONSUMED;
    }

    return GameObject::handleMessage(message);
}

void LightTank::update(const phantom::PhantomTime& time) {
    EnemyMixin::loop();
    GameObject::update(time);
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

void LightTank::onGameObjectDestroyed(GameObject* gameobject) {
    if(gameobject == _victim) {
        stopShooting();
    }
}