#ifndef SITE_H
#define SITE_H

#include <phantom.h>
#include "Edge.h"
#include "HalfEdge.h"

using phantom::Vector3;

namespace PGC{
    class LIBEXPORT Site{
    public:
        Site();
        static Site* createFromIntersect(HalfEdge* he1, HalfEdge* he2);

    private:
        Vector3 coord;
        unsigned int _siteNum;
        unsigned int _refCount;
   };
}

#endif /* SITE_H */