#ifndef LINE2TESTS_H
#define	LINE2TESTS_H

#include "../Test.h"
#include "../../CompileConfig.h"
#include <phantom.h>

using namespace phantom;

class LIBEXPORT Line2Tests : public Test {
public:
    Line2Tests() : Test("Testing Line2 related logic") {

    }

    virtual void run() {
        Line2 defaultCtor;
        if(!assertEquals(defaultCtor.a, 0.0f, 0.0f) || !assertEquals(defaultCtor.b, 0.0f, 0.0f)) {
            trace("The default constructor is broken.");
        }

        Line2 line(Vector3(10.0f, 10.0f), Vector3(100.0f, 100.0f));
        if(!assertEquals(line.a, 10.0f, 10.0f) || !assertEquals(line.b, 100.0f, 100.0f)) {
            trace("The constructor taking two vectors is broken.");
        }

        Line2 floatCtor(99.0f, -23.0f, -204.f, 78.0f);
        if(!assertEquals(floatCtor.a, 99.0f, -23.0f) || !assertEquals(floatCtor.b, -204.f, 78.0f)) {
            trace("The constructor taking four floats is broken.");
        }

        Line2 a(0, 0, 100, 100);
        Line2 b(100, 0, 0, 100);

        if(!assertTrue(a.intersects(b))) {
            trace("Simple intersection test fails. (two lines crossing)");
        }

        if(!assertTrue(b.intersects(a))) {
            trace("Simle intersection test fails (two lines crossing, inversed).");
        }

        Line2 c(101, 101, 200, 200);
        if(!assertFalse(a.intersects(c))) {
            trace("Intersection test false positive. (line extends on line)");
        }

        Line2 d(10, 10, 50, 50);
        if(!assertTrue(a.intersects(d))) {
            trace("Intersection test false positive. (line fits entirely in line)");
        }

        Line2 copy(a);
        if(!assertTrue(a.intersects(copy))) {
            trace("Line does not intersect a copy of itself. This may indicate that the copy ctor is broken.");
        }


    }

};

#endif	/* LINE2TESTS_H */

