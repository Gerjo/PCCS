#include "LightHelicopter.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/HelicopterAttackState.h"
#include "../services/Services.h"

LightHelicopter::LightHelicopter() : _path(1), EnemyMixin(this){
    setType("Helicopter");

    _boundingBox.size.x = 225.0f;
    _boundingBox.size.y = 230.0f;

    _victim = nullptr;
    _attackState = nullptr;
    _idleState = nullptr;

    ArtificialIntelligence *ai = new ArtificialIntelligence(this);
    addComponent(ai);
    _attackState = new HelicopterAttackState(this);
    ai->insertState(_attackState);
    ai->setActive<HelicopterAttackState>();
    
    addComponent(new Mover());

    setHealth(2000.0f);
}

LightHelicopter::~LightHelicopter() {
    if(_attackState)
        delete _attackState;
    if(_idleState)
        delete _idleState;
}

void LightHelicopter::fly(Vector3 location) {
    _path.push_back(location);
    mover->moveTo(_path);

    Data data;
    data("to-x") = location.x;
    data("to-y") = location.y;
    data("x")    = _position.x;
    data("y")    = _position.y;

    _direction = (location - _position).normalize();

    if(residence == GameObject::SERVER)
        Services::broadcast(this, new phantom::Message<Data>(getType() + "-fly-to", data));
}

MessageState LightHelicopter::handleMessage(AbstractMessage *message) {
    if(message->isType(getType() + "-fly-to")) {
        Data data = message->getPayload<Data>();

        _position.x = data("x");
        _position.y = data("y");

        _path.push_back(Vector3(data("to-x"), data("to-y"), 0.0f));

        mover->moveTo(_path);

        return CONSUMED;
    }
    return GameObject::handleMessage(message);
}

void LightHelicopter::fromData(Data &data) {
    GameObject::fromData(data);
}

void LightHelicopter::toData(Data& data) {
    GameObject::toData(data);

    if(_victim != nullptr) {
        data("victim") = _victim->UID_network;
    }
}