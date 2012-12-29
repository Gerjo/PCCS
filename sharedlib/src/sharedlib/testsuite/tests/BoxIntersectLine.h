/*
 * File:   newfile.h
 * Author: gerjo
 *
 * Created on December 29, 2012, 6:47 PM
 */

#ifndef BOXINTERSECTLINE_H
#define	BOXINTERSECTLINE_H

#include "../Test.h"
#include "../../CompileConfig.h"
#include <phantom.h>

using namespace phantom;

class LIBEXPORT BoxIntersectLine : public Test {
public:
    BoxIntersectLine() : Test("Testing 2D intersection between Box3 and Line2") {

    }

    virtual void run() {
        Box3 box(10, 10, 100, 100);
        Line2 line(0, 0, 50, 50);

        if(!assertTrue(box.intersection(line) == Vector3(10.0f, 10.0f, 0.0f))) {
            trace("Intersection test failed, result is not accurate.");
        }

        Box3 box2(-100, -100, 4, 321);
        Line2 line2(-20, -323, -50, -30);
        if(!assertTrue(box2.intersection(line2).isInfinite())) {
            trace("Intersection test false positive, using negative coordinates.");
        }

        Box3 box3(-100, 100, 4, 32);
        Line2 line3(-200, 123, 1200, -30);
        if(!assertTrue(box3.intersection(line3).isFinite())) {
            trace("Intersection test failed.");
        }
    }
};

#endif	/* BOXINTERSECTLINE_H */

