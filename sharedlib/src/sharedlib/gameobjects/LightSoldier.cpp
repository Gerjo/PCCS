#include "LightSoldier.h"
#include "LightFactory.h"
#include "sharedlib/networking/NetworkRegistry.h"

LightSoldier::LightSoldier() : playerId(-1), _victim(nullptr), weapon(nullptr) {
    setType("Soldier");

    _boundingBox.size.x = 50.0f;
    _boundingBox.size.y = 50.0f;

    // Automatically bound to "this->mover".
    addComponent(new Mover());
}

LightSoldier::~LightSoldier() {

}

void LightSoldier::onGameObjectDestroyed(GameObject* gameobject) {
    if(gameobject == _victim) {
        cout << "LightSoldier::onGameObjectDestroyed() Target down!" << endl;
        _victim = nullptr;
    }
}

bool LightSoldier::seekRoute(Vector3 location) {
    Vector3 soldierPos       = getPosition();
    Pathfinding* pathfinding = static_cast<BSPTree*>(_layer)->pathfinding;

    _path.clear();
    deque<Space*> spaces = pathfinding->getPath(soldierPos, location);

    if(spaces.empty()) {
        return false;
    }

    _path.push_back(Vector3(location));

    // We pop the last element, walking to the mouse coords is more
    // sensible than walking to the waypoint. NB: '2' is intentional.
    const int endOffset = 2;

    for(int i = spaces.size() - endOffset; i >= 0; --i) {
        _path.push_back(Vector3(spaces[i]->getCenter()));
    }

    mover->moveTo(&_path);

    return true;
}

void LightSoldier::update(const Time& time) {
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
        ss << "Cannot find route to destination.";
    } else {
        ss << "Walking to location (" << _path.size() << " waypoints).";
    }

    cout << ss.str() << endl;
}

void LightSoldier::onKillSomething(GameObject* gameobject) {
    if(_victim != nullptr && gameobject == _victim) {
        cout << "Soldier: Target down!" << endl;
        _victim = nullptr;
    } else {
        cout << "Soldier: Collateral damage, " << gameobject->getType() << "!" << endl;
    }
}

void LightSoldier::shootAt(UID::Type uid) {
    if(NetworkRegistry::contains(uid)) {
        _victim = NetworkRegistry::get(uid);

        if(_victim == nullptr) {
            cout << "lightsoldier::shootAt() Shooting at nullptr! " << endl;
        }
    } else {
        cout << "lightsoldier::shootAt() Cannot shoot at dead object. " << endl;
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
    }

}

void LightSoldier::fromData(Data& data) {
    GameObject::fromData(data);
    playerId = data("player_id");
}

void LightSoldier::toData(Data& data) {
    GameObject::toData(data);
    data("player_id") = playerId;
}
