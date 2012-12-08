#include "LightTankMech.h"
#include "../networking/NetworkRegistry.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/AttackState.h"
#include "../artificialintelligence/MoveState.h"
#include "../services/Services.h"

LightTankMech::LightTankMech() : EnemyMixin(this) {
    setType("MechTank");

    moveState = nullptr;
    attackState = nullptr;

    _boundingBox.size.x = 120.0f;
    _boundingBox.size.y = 120.0f;
    _killList.push_back("Soldier");

    ArtificialIntelligence *ai = new ArtificialIntelligence();
    addComponent(ai);
    attackState = new AttackState(this, Services::settings()->mech_tank_detection_range);
    moveState = new MoveState(this, Services::settings()->tank_detection_range, Services::settings()->mech_tank_start_driving_range, true);
    ai->insertState(attackState);
    ai->insertState(moveState);
    attackState->construct();
    moveState->construct();

    // Automaticly bound to this->mover.
    addComponent(new Mover());

    setHealth(2000.0f);
}

LightTankMech::~LightTankMech() {
    delete moveState;
    delete attackState;
}

Pathfinding::Route LightTankMech::seekRoute(Vector3 location) {
    Pathfinding* pathfinding = static_cast<BSPTree*>(_layer)->pathfinding;

    Pathfinding::Route _path = pathfinding->getPath(this, location);

    if(_path.empty()) {
        Console::log("LightTankMech.cpp: No route found to destination.");
    }

    mover->moveTo(_path);

    return _path;
}

void LightTankMech::move(const Vector3 &location) {
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
        string broadcastType = getType() + "-move-to";
        Services::broadcast(this, new phantom::Message<Data>(broadcastType, data));
    }
}

MessageState LightTankMech::handleMessage(AbstractMessage *message) {
    if(message->isType(getType() + "-move-to")) {
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

void LightTankMech::update(const phantom::PhantomTime& time) {
    EnemyMixin::loop();
    GameObject::update(time);
}

void LightTankMech::fromData(Data &data) {
    GameObject::fromData(data);
    shootAt(data("victim").toString());
}

void LightTankMech::toData(Data& data) {
    GameObject::toData(data);

    if(_victim != nullptr) {
        data("victim") = _victim->UID_network;
    }
}

void LightTankMech::onGameObjectDestroyed(GameObject* gameobject) {
    if(gameobject == _victim) {
        stopShooting();
    }
}