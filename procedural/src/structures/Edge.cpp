#include "Edge.h"

namespace PGC{
    Edge::Edge(VPoint* s, VPoint* a, VPoint* b): start(s), left(a), right(b), neighbour(0), end(0){
        f = (b->x - a->x) / (a->y - b->y);
        g = s->y - f * s->x;
        direction = new VPoint(b->y - a->y, -(b->x - a->x));
    }
    Edge::~Edge(){
        delete direction;
    }
}