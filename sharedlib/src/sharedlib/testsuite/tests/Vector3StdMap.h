#ifndef VECTORSTDMAP_H
#define	VECTORSTDMAP_H


#include "../Test.h"
#include "../../CompileConfig.h"
#include <phantom.h>
#include <map>

using namespace phantom;

class LIBEXPORT Vector3StdMap : public Test {
public:
    Vector3StdMap() : Test("Vector3 std::map<Vector3, T> lookup bug") {

    }

    virtual void run() {
        std::map<const Vector3, bool> lookup;
        typedef std::pair<const Vector3, bool> lookupPair;


        // Hardcoded values for easy deterministic lookups:
        lookup.insert(lookupPair(Vector3(10.0f, 13.0f, 0.0f), true));
        lookup.insert(lookupPair(Vector3(11.0f, 12.0f, 0.0f), true));
        lookup.insert(lookupPair(Vector3(12.0f, 90.0f, 0.0f), true));
        lookup.insert(lookupPair(Vector3(13.0f, 45.0f, 0.0f), true));
        lookup.insert(lookupPair(Vector3(63.0f, 34.0f, 0.0f), true));
        lookup.insert(lookupPair(Vector3(1.23f, 11.0f, 0.0f), true));

        // Maps use a tree internally, so let us pollute the inner workings:
        for(int i = 0; i < 100; ++i) {
            lookup.insert(lookupPair(Vector3(i * 23.2f, i * 31.33f, 0.0f), true));
        }

        // This has always worked.
        if(! assertFalse( lookup.find(Vector3(12.0f, 90.0f, 0.0f)) == lookup.end() )) {
            trace("Key look up for a low valued key failed.");
        }


        // Tweaked value to trigger the bug (GCC 4.7, vs2012 seems OK):
        Vector3 clone(234.234f, 2344.213f, 0.0f);
        lookup.insert(lookupPair(clone, true));

        // This lookup failed with voronoi related coding:
        if(! assertFalse( lookup.find(clone) == lookup.end() )) {
            trace("Key based lookup failed for pointer copy to value ");

            // Let's search for it manually. After all, the unit test might be
            // broken.
            bool manualSearchFound = false;
            for(auto pair : lookup) {
                if(pair.first == clone) {
                    manualSearchFound = true;
                    break;
                }
            }

            if(manualSearchFound) {
                trace("After a manual lookup, the value was eventually found. This proves that the bug is still there.");
            } else {
                trace("After a manual lookup, the value still was not found."
                      " This implies that the lookup may be working, but that"
                      " the unit test itself is broken.");
            }
        }
    }
};

#endif	/* VECTORSTDMAP_H */

