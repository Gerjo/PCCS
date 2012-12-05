#ifndef ROUTEDETAILS_H
#define	ROUTEDETAILS_H

#include "../gameobjects/GameObject.h"
#include "Pathfinding.h"

typedef deque<Vector3> Route;

struct RouteDetails {
    Entity* entity;
    Route route;
    float distance;

    bool operator<(const RouteDetails& other) const {
        return distance < other.distance;
    }
};

#endif	/* ROUTEDETAILS_H */

