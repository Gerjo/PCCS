#include "VEvent.h"

namespace PGC{
    VEvent::VEvent(VPoint* p, bool isPlaceEvent): point(p),isPlaceEvent(isPlaceEvent),y(p->y),arch(0){

    }
}