#ifndef VORONOI_EVENT_H
#define VORONOI_EVENT_H

#include <CompileConfig.h> 
#include <iostream>

#include "VPoint.h"
#include "Parabola.h"

namespace PGC{
    class LIBEXPORT VEvent{
    public:
        VPoint*     point;
        bool        isPlaceEvent;
        double      y;
        Parabola*   arch;

        VEvent(VPoint* p, bool isPlaceEvent);

        struct CompareEvent : public std::binary_function<VEvent*, VEvent*, bool>{
            bool operator()(const VEvent* l, const VEvent* r) const { 
                return (l->y < r->y);
            }
        };
    };
}

#endif /* VORONOI_EVENT_H */