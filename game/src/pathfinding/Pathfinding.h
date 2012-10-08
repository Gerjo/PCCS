#ifndef PATHFINDING_H
#define	PATHFINDING_H

#include <phantom.h>
#include <vector>
#include <iostream>
#include <queue>

#include "Space.h"

using namespace std;
using namespace phantom;

class Pathfinding : public Composite {
public:
    Pathfinding(EntityLayer& layer);
    void update(const float& elapsed);

    vector<Space*> unfoldRoute(Space* goalSpace, Space* endSpace);

private:
    Space* _root;
    EntityLayer& _layer;
    float _size;


    float calculateHeuristic(Space* goal, Space* testing);
};

#endif	/* PATHFINDING_H */

