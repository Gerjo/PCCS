#ifndef VORONOI_EDGE_H
#define VORONOI_EDGE_H

#include <CompileConfig.h>

namespace PGC{
    class Center;
    class Corner;
    class LIBEXPORT Edge{
    public:
        Edge();
        Center* d0, *d1;
        Corner* v0, *v1;
        bool isTraversable;
        void binaryTraverse(Center* edge);
    };
}

#endif /* VORONOI_EDGE_H */