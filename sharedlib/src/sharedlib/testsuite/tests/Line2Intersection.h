/*
 * File:   Line2Intersection.h
 * Author: gerjo
 *
 * Created on December 28, 2012, 8:03 PM
 */

#ifndef LINE2INTERSECTION_H
#define	LINE2INTERSECTION_H

#include "../Test.h"
#include "../../CompileConfig.h"
#include <phantom.h>

using namespace phantom;

class LIBEXPORT Line2Intersection : public Test {
public:
    Line2Intersection() : Test("Testing Line2 intersection math") {

    }

    virtual void run() {
        Line2 a(1, 1, 3, 3);
        Line2 b(1, 2, 4, 2);

        Vector3 expected(2.0f, 2.0f, 0.0f);

        if(!assertTrue(a.intersection(b) == expected)) {
            trace("Intersection test failed.");
        }

        if(!assertTrue(b.intersection(a) == expected)) {
            trace("Intersection test failed, reversed.");
        }

        Line2 c(10, 20, 40, 20);
        if(!assertTrue(a.intersection(c).isInfinite())) {
            trace("Intersection test false positive, positive coordinates.");
        }

        Line2 d(-101, -200, 100, -20);
        Line2 e(-100, -30, 10, -2);

        if(!assertTrue(d.intersection(e).isInfinite())) {
            trace("Intersection test false positive, mostly negative coordinates");
        }

        Line2 f(-10, -220, -100, -20);
        Line2 g(-100, -30, 10, -20);

        Vector3 result = f.intersection(g);
        if(!assertTrue(result.isFinite())) {
            trace("Intersection test failed, mostly negative coordinates");
        }

        Vector3 expected2(-95.6768f, -29.6069f);
        const float epsilon = 0.1f; // We really don't care about precision.

        if(!assertWithinRange(result.x, expected2.x, epsilon)) {
            trace("Intersection over the x axis not accurate enough.");
        }

        if(!assertWithinRange(result.y, expected2.y, epsilon)) {
            trace("Intersection over the y axis not accurate enough.");
        }

        if(!assertWithinRange(result.z, 0, 0)) {
            trace("The z axis is not zero. We're doing 2D tests, so that is odd.");
            trace("Z value: " + std::to_string(result.z) + ".");
        }
    }
};

#endif	/* LINE2INTERSECTION_H */

