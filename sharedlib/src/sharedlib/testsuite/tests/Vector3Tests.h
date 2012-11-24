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
    }
};

#endif	/* VECTOR3_TESTS */

