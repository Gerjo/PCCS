#include "SquadFlocking.h"

#include "../../gameobjects/GameObject.h"
#include "../../pathfinding/Pathfinding.h"
#include "../../pathfinding/RouteDetails.h"
#include "../ArtificialIntelligence.h"

SquadFlocking::SquadFlocking() : _updateInterval(0.5) {

}

void SquadFlocking::setLeader(GameObject* leader) {
    _leader = leader;
    _updateInterval.expire();
}

void SquadFlocking::construct() {
    AIState::construct();
    _updateInterval.expire();
}

void SquadFlocking::handle(const phantom::PhantomTime& time) {
    if(_updateInterval.hasExpired(time)) {
        _updateInterval.restart();
        Entity* gameobject       = ai->getOwner<Entity*>();
        BSPTree* tree            = static_cast<BSPTree*>(gameobject->getLayer());
        Pathfinding* pathfinding = tree->pathfinding;
        RouteDetails route = pathfinding->getPathDetailled(gameobject, _leader->getBoundingBox().getCenter());


        if(route.distanceSq > 3.0f * 3.0f) {
            Message<Pathfinding::Route> message("mover-set-path", route.route);
            ai->getParent()->handleMessage(&message);
        }

    }
}

void SquadFlocking::destruct() {
    AIState::destruct();
    ai->getParent()->getComponentByType<Mover>(0)->stop();
}