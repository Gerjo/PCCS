#include "SquadMove.h"
#include "../ArtificialIntelligence.h"
#include "../../pathfinding/BSPTree.h"
#include "../../pathfinding/Pathfinding.h"
#include "../../gameobjects/GameObject.h"

SquadMove::SquadMove() {

}

void SquadMove::setTarget(const Vector3& target) {
    _target = target;

    GameObject* gameobject   = static_cast<GameObject*>(ai->getParent());
    BSPTree* tree            = static_cast<BSPTree*>(gameobject->getLayer());
    Pathfinding* pathfinding = tree->pathfinding;
    Pathfinding::Route route = pathfinding->getPath(gameobject, target);

    Message<Pathfinding::Route> message("mover-set-path", route);
    ai->getParent()->handleMessage(&message);
}

void SquadMove::construct() {
    AIState::construct();
}

void SquadMove::update(const phantom::PhantomTime& time) {

}

void SquadMove::destruct() {
    AIState::destruct();
}
