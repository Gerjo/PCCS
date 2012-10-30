#include "LightSoldier.h"
#include "LightFactory.h"

LightSoldier::LightSoldier() : playerId(-1), _victim(0) {
    setType("Soldier");

    init();

    addComponent(weapon);

    // Automatically bound to "this->mover".
    addComponent(new Mover());
}

LightSoldier::~LightSoldier() {
    
}

void LightSoldier::init(void) {
    weapon = (LightWeapon*) LightFactory::create("weapon");
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
    //setShowPath(true);

    return true;
}

void LightSoldier::handleAi(void) {

}

void LightSoldier::attack(GameObject* victim) {
    cout << "attacking" << endl;
}

void LightSoldier::walk(Vector3 location) {
    _victim = 0; // stop shooting. (can change this later on?)
    seekRoute(location);

    stringstream ss;

    if(_path.empty()) {
        ss << "Cannot find route to destination.";
    } else {
        ss << "Walking to location (" << _path.size() << " waypoints).";
    }

    cout << ss.str() << endl;
}

void LightSoldier::fromData(Data& data) {
    GameObject::fromData(data);
    playerId = data("player_id");
}

void LightSoldier::toData(Data& data) {
    GameObject::toData(data);
    data("player_id") = playerId;
}
