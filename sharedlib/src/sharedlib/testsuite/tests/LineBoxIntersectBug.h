/*
 * File:   LineBoxIntersectBug.h
 * Author: gerjo
 *
 * Created on December 29, 2012, 9:13 PM
 */

#ifndef LINEBOXINTERSECTBUG_H
#define	LINEBOXINTERSECTBUG_H

#include "../Test.h"
#include "../../CompileConfig.h"
#include <phantom.h>

using namespace phantom;

class LIBEXPORT LineBoxIntersectBug : public Test {
public:
    LineBoxIntersectBug() : Test("Test box vs line false positive bug.") {

    }

    virtual void run() {

        // These figures trigged the false positive bug:
        Box3 view(126.551, 845.511, 70, 70);
        Line2 a(228.906250,736.718750,228.906250,697.656250);
        Line2 b(404.687500,463.281250,521.875000,482.812500);
        Line2 c(814.843750,453.515625,873.437500,463.281250);

        Vector3 rA = view.intersection(a);
        if(!assertFalse(rA.isFinite())) {
            trace("Intersection test failed. A intersects view.");
            trace("A: " + a.toString());
            trace("view: " + view.toString2());
            trace("result: " + rA.toString2());
        }

        Vector3 rB = view.intersection(a);
        if(!assertFalse(rB.isFinite())) {
            trace("Intersection test failed. B intersects view.");
            trace("B: " + b.toString());
            trace("view: " + view.toString2());
            trace("result: " + rB.toString2());
        }

        Vector3 rC = view.intersection(a);
        if(!assertFalse(rC.isFinite())) {
            trace("Intersection test failed. C intersects view.");
            trace("C: " + c.toString());
            trace("view: " + view.toString2());
            trace("result: " + rC.toString2());
        }
    }
};


#endif	/* LINEBOXINTERSECTBUG_H */

