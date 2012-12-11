#ifndef DATAHELPERTESTS_H
#define	DATAHELPERTESTS_H

#include <string>
#include "../Test.h"
#include "../../CompileConfig.h"
#include "../../serialization/DataHelper.h"
#include "../../pathfinding/Pathfinding.h"

#include <phantom.h>
using namespace phantom;

using std::to_string;

class LIBEXPORT DataHelperTests : public Test {
public:
    DataHelperTests() : Test("DataHelper serialisation tests") {

    }

    virtual void run() {
        Pathfinding::Route routeRandom;
        const int limit = 10000;

        for(int i = 0; i < limit; ++i) {
            routeRandom.push_back(createRandomVector(i));
        }

        Data dataRandom = DataHelper::routeToData(routeRandom);
        Pathfinding::Route cloneRandom = DataHelper::dataToRoute(dataRandom);

        if(!assertTrue( cloneRandom.size() == routeRandom.size())) {
            trace("HUGE route test, not all data was serialized. The size() before is " +
                   to_string(routeRandom.size()) + " the size after is " +
                   to_string(cloneRandom.size()) + ".");
        }

        // Incase the size test fails, we don't want to trigger a random
        // null pointer either.
        auto size = std::min<Pathfinding::Route::size_type>(routeRandom.size(), cloneRandom.size());
        for(int i = 0; i < size; ++i) {
            if(!assertTrue( routeRandom.at(i) == cloneRandom.at(i) )) {
                trace("Failed comparison test at index #" + to_string(i));
                trace(routeRandom[i].toString() + " does not equal " + cloneRandom[i].toString());

                trace("if there are no other unit test errors, then this error probably"
                      " means the order of items was changed during serialize.");

                trace("Aborting further unit tests for this test case.");
                break;
            }
        }



    }

private:
    Vector3 createRandomVector(int i) {
        return Vector3(
                static_cast<float>(i * 22.33f),
                static_cast<float>(i * 234.14f),
                0.0f);
    }
};

#endif	/* DATAHELPERTESTS_H */

