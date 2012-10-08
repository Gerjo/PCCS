#ifndef PATHFINDING_H
#define	PATHFINDING_H

#include <phantom.h>
#include <vector>
#include <iostream>
#include <queue>
#include <time.h>
#include "Space.h"
#include "BSPTree.h"

using namespace std;
using namespace phantom;

class Pathfinding : public Composite {
public:
    Pathfinding(BSPTree& layer);
    void update(const float& elapsed);

    void drawRect(Box3& area, Color color);
    void drawRect(Space* whom,  Color color);

    void getPath(Vector3& start, Vector3& goal);
private:
    float calculateHeuristic(Space* goal, Space* testing);
    vector<Space*> unfoldRoute(Space* unfoldee, Space* Limit);
    BSPTree& _layer;
};

#endif	/* PATHFINDING_H */

