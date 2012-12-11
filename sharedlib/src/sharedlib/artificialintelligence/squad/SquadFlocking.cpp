#include "SquadFlocking.h"

#include "../../gameobjects/GameObject.h"
#include "../../pathfinding/Pathfinding.h"
#include "../../pathfinding/RouteDetails.h"
#include "../ArtificialIntelligence.h"

SquadFlocking::SquadFlocking() : _updateInterval(0.1) {

}

void SquadFlocking::setLeader(GameObject* leader) {
    _leader = leader;
}

void SquadFlocking::construct() {
    AIState::construct();
}

void SquadFlocking::handle(const phantom::PhantomTime& time) {
    if(_updateInterval.hasExpired(time)) {
        _updateInterval.restart();


        BSPTree* tree            = static_cast<BSPTree*>(_leader->getLayer());
        Pathfinding* pathfinding = tree->pathfinding;
        RouteDetails route = pathfinding->getPathDetailled(_leader, _leader->getBoundingBox().getCenter());


        //if(route.distanceSq > 1.0f) {
            Message<Pathfinding::Route> message("mover-set-path", route.route);
            ai->getParent()->handleMessage(&message);
        //}

    }
}

void SquadFlocking::destruct() {
    AIState::destruct();
    ai->getParent()->getComponentByType<Mover>(0)->stop();
}