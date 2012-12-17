#ifndef DATAHELPER_H
#define	DATAHELPER_H

#include <phantom.h>
#include <deque>
#include "../CompileConfig.h"
#include "../pathfinding/Pathfinding.h"
#include "Data.h"

using namespace phantom;
using std::deque;


class LIBEXPORT DataHelper {
public:

    static Data routeToData(Pathfinding::Route& route) {
        Data data;

        int i = 0;
        for(Vector3& waypoint : route) {

            data(i)("x") = waypoint.x;
            data(i)("y") = waypoint.y;
            // z is intentionally skipped.
            ++i;
        }

        return data;
    }

    static Pathfinding::Route dataToRoute(Data& data) {
        Pathfinding::Route route;
        vector<Data> asVector = data.toVector<Data>();

        for(Data& waypoint : asVector) {
            float x = waypoint("x");
            float y = waypoint("y");
            // z is intentionally skipped.

            route.push_back(Vector3(x, y, 0.0f));
        }

        return route;
    }

};

#endif	/* DATAHELPER_H */

