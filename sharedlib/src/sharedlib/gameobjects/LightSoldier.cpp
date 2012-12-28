#include "LightSoldier.h"
#include "LightFactory.h"
#include "sharedlib/networking/NetworkRegistry.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/squad/SquadMove.h"
#include "../artificialintelligence/squad/SquadFlocking.h"
#include "../artificialintelligence/squad/SquadAttack.h"
#include "../services/Services.h"
#include "../models/Squad.h"
#include "../pathfinding/PathWalker.h"

LightSoldier::LightSoldier() : playerId(-1), _victim(nullptr), weapon(nullptr) {
    setType("Soldier");
    setHealth(100.0f);

    _boundingBox.size.x = 50.0f;
    _boundingBox.size.y = 50.0f;
    _killList.push_back("Tank");
    _killList.push_back("Helicopter");


    ArtificialIntelligence::soldiers.push_back(this);

    addComponent(ai = new ArtificialIntelligence());
    ai->runat = GameObject::BOTH;

    ai->insertState(new SquadMove());
    ai->insertState(new SquadFlocking());
    ai->insertState(new SquadAttack());

    addComponent(new PathWalker());
}

LightSoldier::~LightSoldier() {
    auto it = find(ArtificialIntelligence::soldiers.begin(), ArtificialIntelligence::soldiers.end(), this);
    ArtificialIntelligence::soldiers.erase(it);
}

bool LightSoldier::canShootAt(Entity* gameobject) {
    for(string s : _killList) {
        if(gameobject->isType(s))
            return true;
    }

    // Cannot shoot. This generally means that we can walk to this location. Eg:
    // you click on a crate and will walk to said crate, rather than shoot at it.
    return false;
}

void LightSoldier::onCollision(Composite* other, CollisionData& collisionData) {

    // This is better for flocking. Have the other soldiers form around
    // the leader. Disabling this just gives funnier results :p
    if(false && isSquadLeader()) {
        // This is great, but you can "push" other players:
        //if(hasSquad() && squad->size() > 1) {
            return;
        //}
    }

    Vector3 direction = directionTo(static_cast<Entity*>(other));
    Pulse pulse;
    pulse.direction = direction.reverse();

    if(other->isType("Soldier")) {
        //if(hasSquad() && squad->isLeader(static_cast<GameObject*>(other))) {
        //    pulse.speed     = Services::settings()->pulse_soldier_vs_leader_speed;
        //    pulse.weight    = Services::settings()->pulse_soldier_vs_leader_weight;
        //    pulse.friction  = Services::settings()->pulse_soldier_vs_leader_friction;
        //} else {
            pulse.speed     = 30;//Services::settings()->pulse_soldier_vs_soldier_speed;
            pulse.weight    = 1;//Services::settings()->pulse_soldier_vs_soldier_weight;
            pulse.friction  = 10;//Services::settings()->pulse_soldier_vs_soldier_friction;
        //}
    } else {
        //pulse.speed     = Services::settings()->pulse_soldier_vs_any_speed;
        //pulse.weight    = Services::settings()->pulse_soldier_vs_any_weight;
        //pulse.friction  = Services::settings()->pulse_soldier_vs_any_friction;
    }

    Message<Pulse> message("add-pulse", pulse);
    handleMessage(&message);

    collisionData.wasHandled = false;
}

void LightSoldier::update(const PhantomTime& time) {
    GameObject::update(time);
}

MessageState LightSoldier::handleMessage(AbstractMessage* message) {
    if(message->isType("disconnect")) {
        onDestruction();
        return CONSUMED;

    } else if(message->isType("gameobject-destroyed")) {
        GameObject* gameobject = message->getPayload<GameObject*>();

        if(gameobject == _victim) {
            cout << "LightSoldier::handleMessage() Target down!" << endl;
            _victim = nullptr;
        }
    }

    // We are moving:
    if(message->isType("ssssssssmover-set-path")) {
        auto route = message->getPayload<Pathfinding::Route>();
        Data data  = DataHelper::routeToData(route);
        mover->moveTo(route);

        // The network shall automatically delete this message.
        auto networkMessage = new Message<Data>("mover-sync-path", data);

        Services::broadcast(this, networkMessage);

        return CONSUMED;
    }

    // The soldier moved on another PC, we're receiving a sync message.
    if(message->isType("mover-sync-path")) {
        Data data  = message->getPayload<Data>();
        auto route = DataHelper::dataToRoute(data);
        mover->moveTo(route);

        return CONSUMED;
    }

    // The soldier moved on another PC, we're receiving a sync message.
    if(message->isType("mover-stop")) {
        mover->stop();
        return HANDLED; // HANDLED, there are more listeners.
    }

    if(message->isType("bullet-fired")) {
        //LightBullet* bullet = message->getPayload<LightBullet*>();
        return CONSUMED;
    }

    if(message->isType("victim-reset")) {
        // GameObject* oldVictim = message->getPayload<GameObject*>();
        return CONSUMED;
    }

    if(message->isType("victim-change")) {
        // GameObject* newVictim = message->getPayload<GameObject*>();
        return CONSUMED;
    }

    return GameObject::handleMessage(message);
}

void LightSoldier::fromData(Data& data) {
    GameObject::fromData(data);
    playerId = data("player_id");
}

void LightSoldier::toData(Data& data) {
    GameObject::toData(data);
    data("player_id") = playerId;


    if(_victim != nullptr) {
        data("victim") = _victim->UID_network;
    }
}

bool LightSoldier::isSquadLeader() {
    return squad != nullptr && squad->isLeader(this);
}

bool LightSoldier::hasSquad() const {
    return squad != nullptr;
}
