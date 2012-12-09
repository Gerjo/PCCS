#include "LightSoldier.h"
#include "LightFactory.h"
#include "sharedlib/networking/NetworkRegistry.h"
#include "../artificialintelligence/ArtificialIntelligence.h"
#include "../artificialintelligence/soldier/IdleState.h"
#include "../artificialintelligence/soldier/WalkState.h"
#include "../artificialintelligence/soldier/FlockState.h"

LightSoldier::LightSoldier() : playerId(-1), _victim(nullptr), weapon(nullptr) {
    setType("Soldier");

    _boundingBox.size.x = 50.0f;
    _boundingBox.size.y = 50.0f;
    _killList.push_back("Tank");
    _killList.push_back("Helicopter");

    // Automatically bound to "this->mover".
    addComponent(new Mover());
    ArtificialIntelligence::soldiers.push_back(this);

    addComponent(ai = new ArtificialIntelligence(this));
    ai->runat = GameObject::BOTH;

    ai->insertState(new IdleState());
    ai->insertState(new WalkState());
    ai->insertState(new FlockState());

    ai->setActive<IdleState>();
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

void LightSoldier::onCollision(Composite* other) {
    if(other->isType("Soldier")) {
        LightSoldier* soldier = static_cast<LightSoldier*>(other);

        // Permit walking through other players' soldiers
        if(soldier->playerId != this->playerId) {
            return;
        }

        return;
        // Disabled, this is a WIP.
        if(!soldier->mover->isPaused()) {
            mover->pause(rand() % 1200);
        }

        /*
        // Let us determine the collision normals. This is quite trivial since
        // we use the most basic physics ever.
        Vector3 normals(1, 1, 0);
        if(_position.x < other->getPosition().x) {
            normals.x = -1;
        }

        if(_position.y < other->getPosition().y) {
            normals.y = -1;
        }

        Box3 intersection = _boundingBox.getIntersectionNaive(other->getBoundingBox());
        intersection.size *= 0.5;


        addPosition(normals * intersection.size);
        */
    }
}

void LightSoldier::onGameObjectDestroyed(GameObject* gameobject) {
    if(gameobject == _victim) {
        cout << "LightSoldier::onGameObjectDestroyed() Target down!" << endl;
        _victim = nullptr;
    }
}

bool LightSoldier::seekRoute(Vector3 location) {
    Pathfinding* pathfinding = static_cast<BSPTree*>(_layer)->pathfinding;

    _path = pathfinding->getPath(this, location);

    if(_path.empty()) {
        Console::log("Soldier.cpp: No route found to destination.");
        return false;
    }

    mover->moveTo(_path);

    return true;
}

void LightSoldier::update(const PhantomTime& time) {
    GameObject::update(time);
}

void LightSoldier::onBulletFired(LightBullet* bullet){

}

void LightSoldier::attack(GameObject* victim) {
    Box3& boundingbox = victim->getBoundingBox();
    walk(boundingbox.getCenter());

    _victim = victim;
    _victim->registerDestoryEvent(this);
}

void LightSoldier::walk(Vector3 location) {
    _victim = nullptr; // stop shooting. (can change this later on?)
    seekRoute(location);

    stringstream ss;

    if(_path.empty()) {
        ss << "Soldier: Cannot find route to destination.";
    } else {
        ss << "Soldier: Walking to location (" << _path.size() << " waypoints).";
    }

    Console::log(ss.str());
}

void LightSoldier::shootAt(UID::Type uid) {
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

void LightSoldier::stopShooting() {
    _victim = nullptr;
}

MessageState LightSoldier::handleMessage(AbstractMessage* message) {
    if(message->isType("Soldier-walk-to")) {
        stopShooting();
        Data data = message->getPayload<Data>();

        // Our amazing position integration:
        _position.x = data("x");
        _position.y = data("y");

        seekRoute(Vector3(data("to-x"), data("to-y"), 0.0f));

        return CONSUMED;

    } else if(message->isType("Soldier-shoot-start")) {
        Data data = message->getPayload<Data>();
        shootAt(data("victim").toString());
        return CONSUMED;

    } else if(message->isType("Soldier-shoot-stop")) {
        stopShooting();
        return CONSUMED;

    } else if(message->isType("disconnect")) {
        onDestruction();
        return CONSUMED;
    }

    return GameObject::handleMessage(message);
}

void LightSoldier::fromData(Data& data) {
    GameObject::fromData(data);
    playerId = data("player_id");

    // No checks required, this will silently fail if the victim isn't valid.
    shootAt(data("victim").toString());
}

void LightSoldier::toData(Data& data) {
    GameObject::toData(data);
    data("player_id") = playerId;


    if(_victim != nullptr) {
        data("victim") = _victim->UID_network;
    }
}

void LightSoldier::formationFollow(LightSoldier* leader) {

}

void LightSoldier::formationLeadTheWay(LightSoldier* leader) {

}
