#include "LightHelicopter.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/AttackState.h"
#include "../artificialintelligence/MoveState.h"
#include "../services/Services.h"

LightHelicopter::LightHelicopter() : EnemyMixin(this){
    setType("Helicopter");

    _boundingBox.size.x = 225.0f;
    _boundingBox.size.y = 230.0f;

    _victim = nullptr;
    _attackState = nullptr;
    _moveState = nullptr;

    ArtificialIntelligence *ai = new ArtificialIntelligence();
    addComponent(ai);
    _attackState = new AttackState(this, Services::settings()->helicopter_detection_range);
    _moveState = new MoveState(this, Services::settings()->helicopter_detection_range, Services::settings()->helicopter_start_flying_range, false);
    ai->runat = GameObject::SERVER;
    ai->insertState(_attackState);
    ai->insertState(_moveState);
    _attackState->construct();
    _moveState->construct();

    addComponent(new Mover());
    mover->setMovementSpeed(Services::settings()->helicopter_movement_speed);
    setHealth(2000.0f);
}

LightHelicopter::~LightHelicopter() {
    delete _attackState;
    delete _moveState;
}

void LightHelicopter::move(const Vector3 &location) {
    if(!mover->isStopped())
        return;

    mover->moveTo(location);

    Data data;
    data("to-x") = location.x;
    data("to-y") = location.y;
    data("x")    = _position.x;
    data("y")    = _position.y;

    _direction = (location - _position).normalize();

    if(residence == GameObject::SERVER)
        Services::broadcast(this, new phantom::Message<Data>(getType() + "-move-to", data));
}

MessageState LightHelicopter::handleMessage(AbstractMessage *message) {
    if(message->isType(getType() + "-move-to")) {
        Data data = message->getPayload<Data>();

        _position.x = data("x");
        _position.y = data("y");

        mover->moveTo(Vector3(data("to-x"), data("to-y"), 0.0f));

        return CONSUMED;
    }
    else if(message->isType(getType() + "shoot-start")) {
        Data data = message->getPayload<Data>();
        shootAt(data("victim").toString());
        return CONSUMED;
    }
    else if(message->isType(getType() + "shoot-stop")) {
        stopShooting();
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