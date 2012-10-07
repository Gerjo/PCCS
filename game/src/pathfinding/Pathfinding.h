#ifndef PATHFINDING_H
#define	PATHFINDING_H

#include <phantom.h>
#include <vector>
#include <iostream>

#include "Space.h"

using namespace std;
using namespace phantom;

class Pathfinding : public Composite {
public:
    Pathfinding(EntityLayer& layer);
    void update(const float& elapsed);
    
private:
    Space* _root;
    EntityLayer& _layer;
    float _size;
};

#endif	/* PATHFINDING_H */

