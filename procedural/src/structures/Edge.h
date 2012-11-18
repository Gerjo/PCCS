#ifndef VORONOI_EDGE_H
#define VORONOI_EDGE_H

#include <CompileConfig.h>

#include "VPoint.h"

namespace PGC{
    class LIBEXPORT Edge{
    public:
        VPoint *start, *end, *direction, *left, *right;
        double f, g;
        Edge* neighbour;
    
        Edge(VPoint* s, VPoint* a, VPoint* b);
        ~Edge();
    };
}

#endif /* VORONOI_EDGE_H */