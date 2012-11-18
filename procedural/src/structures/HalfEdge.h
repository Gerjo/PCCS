#ifndef HALFEDGE_H
#define HALFEDGE_H

#include "Edge.h"

namespace PGC{
    class LIBEXPORT HalfEdge{
    public:
        HalfEdge();
    private:
        HalfEdge* _ELleft;
        HalfEdge* _elRight;
        Edge* _ELedge;
        unsigned int _ELrefCount;
        char _ELpm;
        float yStar;
        HalfEdge* PQnext;
    };
}

#endif /* HALFEDGE_H */