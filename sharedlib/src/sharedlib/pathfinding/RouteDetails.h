#ifndef ROUTEDETAILS_H
#define	ROUTEDETAILS_H

#include <phantom.h>

typedef deque<Vector3> Route;

struct RouteDetails {
    RouteDetails(phantom::Entity* _entity, Route _route, float _distanceSq) :
        entity(_entity), route(_route), distanceSq(_distanceSq) {

    }

    Entity* entity;
    Route route;
    float distanceSq;

    bool operator<(const RouteDetails& other) const {
        return distanceSq < other.distanceSq;
    }
};

#endif	/* ROUTEDETAILS_H */

