#ifndef WALKSTATE_H
#define	WALKSTATE_H

#include "../AIState.h"
#include "../../pathfinding/BSPTree.h"

// tmp:
#include <iostream>
using std::cout;
using std::endl;

class WalkState : public AIState {
public:
    WalkState() {

    }

    void setTarget(const Vector3& target) {
        _target = target;
        GameObject* gameobject = static_cast<GameObject*>(ai->getParent());

        BSPTree* tree = static_cast<BSPTree*>(gameobject->getLayer());
        Pathfinding* pathfinding = tree->pathfinding;

        Pathfinding::Route route = pathfinding->getPath(gameobject, target);

        gameobject->getComponentByType<Mover>(0)->moveTo(route);

        cout << "I SHALL WALK THERE." << endl;
    }

    virtual void construct() {
        AIState::construct();

        cout << "construct IdleState" << endl;
    }

    virtual void handle(const phantom::PhantomTime& time) {

    }

    virtual void destruct() {
        AIState::destruct();

    }

private:
    Vector3 _target;
};

#endif	/* WALKSTATE_H */

