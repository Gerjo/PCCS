#ifndef VECTOR3_TESTS
#define	VECTOR3_TESTS

#include "../Test.h"
#include "../../CompileConfig.h"
#include <phantom.h>

using namespace phantom;

class LIBEXPORT Vector3Tests : public Test {
public:
    Vector3Tests() : Test("Basic Vector3 arithmetic") {

    }

    virtual void run() {
        Vector3 a(123.456f, 5333.342f, -123.333333f);
        Vector3 b(123.456f, 5333.342f, -123.333333f);
        Vector3 c(1223.456f, 1.0f, 0.f);

        if(!assertTrue(a == b)) {
            trace("Comparing equal vectors did not yield true.");
        }

        if(!assertFalse(a == c)) {
            trace("Comparing not equal vectors did not yield false.");
        }

        Vector3 d(100.0f, 200.0f, 300.0f);
        Vector3 e(101.0f, 202.0f, 303.0f);
        Vector3 sum = d + e;

        if(!assertTrue(d.x + e.x == sum.x && d.y + e.y == sum.y && d.z + e.z == sum.z)) {
            trace("Adding two vectors failed.");
        }

        Vector3 f(100.0f, 200.0f, 300.0f);
        float dot = f.dot(Vector3(99.0f, -99.9f, -1.0f));

        if(!assertTrue(dot == -10380)) {
            trace("Unable to calculate a dot product.");
        }


        Vector3 g(199.342f, -99.23f, 0.0f);
        Vector3 perp = g.perp();

        if(!assertTrue(perp.dot(g) == 0.0f)) {
            trace("Unable to calculate the 2D perpendicular vector.");
        }

        Vector3 h(-199.0f, 1.0f, 33.0f);
        Vector3 i(129.0f, -231.0f, -23.0f);
        Vector3 cross = h.cross(i);

        if(!assertTrue(cross.x == 7600.0f && cross.y == -320.0f && cross.z == 45840.0f)) {
            trace("Unable to calculate a correct cross product.");
        }

        Vector3 foo(1231, 1234), bar(231, 8654);
        const float distance = foo.distanceTo(bar);
        const float expected = 7487.082209;
        if(!assertTrue(distance == expected)) {
            trace("Unable to calculate a correct length.");
            trace(std::to_string(distance) + " != " + std::to_string(expected));
        }


    }
};

#endif	/* VECTOR3_TESTS */

