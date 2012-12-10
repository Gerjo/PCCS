#ifndef PATHFINDING_H
#define	PATHFINDING_H

#include <phantom.h>
#include <vector>
#include <iostream>
#include <queue>
#include <time.h>
#include <sstream>
#include "Space.h"
#include "BSPTree.h"
#include "../CompileConfig.h"
#include "../gameobjects/GameObject.h"
#include "RouteDetails.h"

using namespace std;
using namespace phantom;

class LIBEXPORT Pathfinding : public GameObject {
public:
    typedef deque<Vector3> Route;

    Pathfinding(BSPTree& layer);

    void drawRect(Box3& area, Color color);
    void drawRect(Space* whom,  Color color);

    Route getPath(Entity* entity, const Vector3& goal);
    RouteDetails getPathDetailled(Entity* entity, const Vector3& goal);

private:
    float calculateHeuristic(Space* goal, Space* testing);
    void unfoldRoute(Route& out, Space* unfoldee, Space* Limit, Entity* entity);
    BSPTree& _layer;

    bool _showDebug;
    bool _showBasicDebug;
    bool _visualize;
};

#endif	/* PATHFINDING_H */

