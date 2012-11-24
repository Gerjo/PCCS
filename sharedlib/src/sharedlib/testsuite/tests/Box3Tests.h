#ifndef BOX3TESTS_H
#define	BOX3TESTS_H

#include "../Test.h"
#include "../../CompileConfig.h"
#include <phantom.h>

using namespace phantom;

class LIBEXPORT Box3Tests : public Test {
public:
    Box3Tests() : Test("Testing Box3 related logic") {

    }

    virtual void run() {

        Box3 large(-10, -10, 100, 100);
        Box3 inside(10, 10, 10, 10);

        if(!assertTrue(large.intersect(inside)) || !assertTrue(inside.intersect(large))) {
            trace("Box in box intersection test failed. ");
        }

        Box3 farAway(1000, 1000, 100, 100);

        if(!assertFalse(large.intersect(farAway)) || !assertFalse(farAway.intersect(large))) {
            trace("Box in box intersection test failed. Returned a false positive. ");
        }

        Box3 negative(10, 10, -200, -200);
        Box3 test(-100, 100, 200, -200);

        trace("(warning) applied 'repair hack' to boxes.");
        test.repair();
        negative.repair();

        if(!assertTrue(negative.intersect(test)) || !assertTrue(test.intersect(negative))) {
            trace("Negative width/height box in box intersection test failed. ");
            trace(negative.toString2() + " does not fit in " + test.toString2());
        }

        Box3 negative2(10, 10, -200, -200);
        Box3 test2(-100, 100, 200, 200);

        if(!assertFalse(negative2.intersect(test2)) || !assertFalse(test2.intersect(negative2))) {
            trace("Negative width/height box in box intersection test failed. Return a false positive. ");
        }

        Vector3 v(60.0f, 60.0f);

        if(!assertTrue(large.contains(v))) {
            trace("Point in box failed.");
        }

        if(!assertFalse(farAway.contains(v))) {
            trace("Point in box failed. Returned a false positive.");
        }

    }
};

#endif	/* BOX3TESTS_H */

