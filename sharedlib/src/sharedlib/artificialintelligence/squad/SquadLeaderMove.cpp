#include "SquadLeaderMove.h"
#include "../ArtificialIntelligence.h"
#include "../../pathfinding/BSPTree.h"
#include "../../pathfinding/Pathfinding.h"
#include "../../gameobjects/GameObject.h"

WalkState::WalkState() {

}

void WalkState::setTarget(const Vector3& target) {
    _target = target;

    GameObject* gameobject   = static_cast<GameObject*>(ai->getParent());
    BSPTree* tree            = static_cast<BSPTree*>(gameobject->getLayer());
    Pathfinding* pathfinding = tree->pathfinding;
    Pathfinding::Route route = pathfinding->getPath(gameobject, target);

    Message<Pathfinding::Route> message("mover-set-path", route);
    ai->getParent()->handleMessage(&message);
}

void WalkState::construct() {
    AIState::construct();
}

void WalkState::handle(const phantom::PhantomTime& time) {

}

void WalkState::destruct() {
    AIState::destruct();
    ai->getParent()->getComponentByType<Mover>(0)->stop();
}
