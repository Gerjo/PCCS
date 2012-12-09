#ifndef ROUTEDETAILS_H
#define	ROUTEDETAILS_H

#include <phantom.h>

typedef deque<Vector3> Route;

struct RouteDetails {
    RouteDetails(phantom::Entity* _entity, Route _route, float _distance) :
        entity(_entity), route(_route), distance(_distance) {

    }

    Entity* entity;
    Route route;
    float distance;

    bool operator<(const RouteDetails& other) const {
        return distance < other.distance;
    }
};

#endif	/* ROUTEDETAILS_H */

