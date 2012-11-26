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


        Box3 box1(10, 10, 100, 100);
        Line2 line1(20, 20, 100, 1000);


        if(!assertTrue(box1.intersect(line1))) {
            trace("Line2 intersect with Box3 failed. (a)");
        }

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
        negative.repair();
        test.repair();
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


        Box3 box2(-100, -102, 10, 100);
        Line2 line2(-200, -200, 100, 200);
        if(!assertTrue(box2.intersect(line2))) {
            trace("Line2 intersect with Box3 failed. (b)");
        }

        Box3 box3(-100, -102, -10, 100);
        Line2 line3(200, -200, 100, 200);
        if(!assertFalse(box3.intersect(line3))) {
            trace("Line2 intersect with Box3 failed. (c) false positive");
        }

        Box3 box4(-80, -222, -10, 100);
        Line2 line4(100, 100, -100, -220);
        if(!assertTrue(box4.intersect(line4))) {
            trace("Negative Line2 intersect with Box3 failed. (d)");
        }

        Box3 box5(-100, -120, -200, -100);
        Line2 line5(-120, -10, -200, -200);
        if(!assertTrue(box5.intersect(line5))) {
            trace("Negative Line2 intersect with negative Box3 failed. (e)");
        }


        Box3 box6(-100, -120, -200, -100);
        Line2 line6(-120, -10, -160, -110);

        if(!assertFalse(box6.intersect(line6))) {
            trace("Negative Line2 intersect with negative Box3 failed. (f) false positive");
        }

    }
};

#endif	/* BOX3TESTS_H */

