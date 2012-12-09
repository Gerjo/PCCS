#include "SquadFlock.h"

#include "../../gameobjects/GameObject.h"
#include "sharedlib/pathfinding/Pathfinding.h"
#include "../ArtificialIntelligence.h"

FlockState::FlockState() : _updateInterval(1) {

}

void FlockState::setLeader(GameObject* leader) {
    _leader = leader;

    cout << "flocking.." << endl;
}

void FlockState::construct() {
    AIState::construct();
}

void FlockState::handle(const phantom::PhantomTime& time) {
    if(_updateInterval.hasExpired(time)) {
        _updateInterval.restart();


        BSPTree* tree            = static_cast<BSPTree*>(_leader->getLayer());
        Pathfinding* pathfinding = tree->pathfinding;
        Pathfinding::Route route = pathfinding->getPath(_leader, _leader->getBoundingBox().getCenter());

        ai->getParent()->getComponentByType<Mover>(0)->moveTo(route);
    }
}

void FlockState::destruct() {
    AIState::destruct();
    ai->getParent()->getComponentByType<Mover>(0)->stop();
}