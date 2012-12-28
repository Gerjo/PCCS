#include "SquadFlocking.h"

#include "../../gameobjects/GameObject.h"
#include "../../pathfinding/Pathfinding.h"
#include "../../pathfinding/RouteDetails.h"
#include "../ArtificialIntelligence.h"

SquadFlocking::SquadFlocking() : _leader(nullptr), _updateInterval(0.5) {

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
    if(_leader == nullptr) {
        cout << "SquadFlocking::handle(): Flocking without leader. Enjoy the possible segfault." << endl;
    }

    Vector3 destination = _leader->getPosition();
    float distance = ai->getParent()->getPosition().distanceTo(destination);

    if(distance < _leader->getBoundingBox().size.y) {
        AbstractMessage message("halt");
        ai->getParent()->handleMessage(&message);
        return;
    }

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

MessageState SquadFlocking::handleMessage(AbstractMessage* message) {
    if(message->isType("gameobject-destroyed")) {
        GameObject* victim = message->getPayload<GameObject*>();
        if(_leader == victim) {
            _leader = nullptr;
        }
    }

    return IGNORED;
}

