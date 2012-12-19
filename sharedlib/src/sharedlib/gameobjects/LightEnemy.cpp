#include "LightEnemy.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/AIState.h"
#include "../artificialintelligence/AttackState.h"
#include "../artificialintelligence/MoveState.h"
#include "../pathfinding/Pathfinding.h"
#include "../services/Services.h"
#include <string>

LightEnemy::LightEnemy(Data enemyinfo) : EnemyMixin(this), _initialEnemyInfo(enemyinfo), _movethrough((int)_initialEnemyInfo(string("movethrough")) == 1) {
    setType("Enemy");
    _boundingBox.size.x = enemyinfo(string("boxsizex"));
    _boundingBox.size.y = enemyinfo(string("boxsizey"));
    addComponent(new Mover());
    mover->setMovementSpeed(enemyinfo(string("movementspeed")));

    ai = new ArtificialIntelligence();
    addComponent(ai);
    ai->runat = GameObject::SERVER;

    Data aistates = enemyinfo(string("artificialintelligence"));
    if(aistates.hasKey("attackstate")) {
        insertAndActivateInAI(new AttackState(this, enemyinfo(string("attackrange"))));
    }
    else if(aistates.hasKey("movestate")) {
        insertAndActivateInAI(new MoveState(this, enemyinfo("detectrange"), enemyinfo("maxdistancefromsoldier"), (int)enemyinfo("lineofsight") == 1));
    }
}

LightEnemy::~LightEnemy() {
}

void LightEnemy::insertAndActivateInAI(AIState *state) {
    ai->insertState(state);
    state->construct();
    _AIstates.push_back(state);
}

void LightEnemy::move(const Vector3 &location) {
    if(!mover->isStopped())
        return;

    if(!_movethrough) {
        mover->moveTo(location);
    }
    else {
        Pathfinding::Route _path = static_cast<BSPTree*>(_layer)->pathfinding->getPath(this, location);
        mover->moveTo(_path);
    }

    _direction = (location - _position).normalize();

    if(residence == GameObject::SERVER) {
        Data data;
        data("to-x") = location.x;
        data("to-y") = location.y;
        data("x")    = _position.x;
        data("y")    = _position.y;
        Services::broadcast(this, new phantom::Message<Data>(getType() + "-move-to", data));
    }
}

MessageState LightEnemy::handleMessage(AbstractMessage *message) {
    if(message->isType(getType() + "-move-to")) {
        Data data = message->getPayload<Data>();

        _position.x = data("x");
        _position.y = data("y");

        move(Vector3(data("to-x"), data("to-y"), 0.0f));

        return CONSUMED;

    } 
    else if(message->isType(getType() + "-shoot-start")) {
        Data data = message->getPayload<Data>();
        shootAt(data("victim").toString());
        return CONSUMED;

    } 
    else if(message->isType(getType() + "-shoot-stop")) {
        stopShooting();
        return CONSUMED;

    } 
    else if(message->isType("gameobject-destroyed")) {
        GameObject* gameobject = message->getPayload<GameObject*>();

        if(gameobject == _victim) {
            stopShooting();
        }
    }

    return GameObject::handleMessage(message);
}

void LightEnemy::toData(Data& data) {
    GameObject::toData(data);
    data("name")        = _initialEnemyInfo("name");
}