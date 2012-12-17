#ifndef COMPLEXDATATESTS_H
#define	COMPLEXDATATESTS_H


#include "../Test.h"
#include "../../CompileConfig.h"
#include <phantom.h>
#include "../../serialization/Data.h"

using namespace phantom;

using std::string;

class LIBEXPORT ComplexDataTests : public Test {
public:
    ComplexDataTests() : Test("Testing if 'return i + 1' serialization bug is fixed") {

    }

    virtual void run() {
        Data data;

        Data subData;
        subData(1) = "one";
        subData(2) = "two";
        subData(3) = "three";
        subData(4) = "four";

        data("root") = "_root";
        data("subdata") = subData; // This is the culprit we're testing.
        data("type") = "_type";

        Data clone = Data::fromJson(data.toJson());

        if(! assertTrue((string) clone("subdata")(1) == "one" )) {
            trace("sub collection fail.");
        }

        if(! assertTrue((string) clone("root") == "_root" )) {
            trace("_root collection fail.");
        }

        if(! assertTrue((string) clone("type") == "_type" )) {
            trace("_type collection fail.");
        }



        // Tailored to match a specific bug:
        string complexJson = "{\"UID_network\": \"UID382\",\"payload\": {\"0\": {\"x\": \"326.562500\",\"y\": \"463.281250\"},\"1\": {\"x\": \"404.687500\",\"y\": \"463.281250\"},\"2\": {\"x\": \"444.090912\",\"y\": \"476.520111\"}},\"type\": \"mover-sync-path\"}";

        Data restored = Data::fromJson(complexJson);

        if(! assertTrue((string)restored("type") == "mover-sync-path") ) {
            trace("Bug! fromJson fails with large node-nesting-depth.");
        }

    }
};

#endif	/* COMPLEXDATATESTS_H */

