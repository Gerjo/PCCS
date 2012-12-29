#include "TestSuite.h"

#define RULER  << endl << "----------------------------------------" << endl

#include "tests/TestingTests.h"
#include "tests/Vector3Tests.h"
#include "tests/Line2Tests.h"
#include "tests/Box3Tests.h"
#include "tests/DataTests.h"
#include "tests/DataHelperTests.h"
#include "tests/ComplexDataTests.h"
#include "tests/Vector3StdMap.h"
#include "tests/Line2Intersection.h"
#include "tests/BoxIntersectLine.h"
#include "tests/LineBoxIntersectBug.h"

TestSuite::TestSuite() {
    //runSingle(new BoxIntersectLine());

    addTest(new TestingTests());
    addTest(new Vector3Tests());
    addTest(new Line2Tests());
    addTest(new Box3Tests());
    addTest(new DataTests());
    addTest(new DataHelperTests());
    addTest(new ComplexDataTests());
    addTest(new Vector3StdMap());
    addTest(new Line2Intersection());
    addTest(new BoxIntersectLine());
    addTest(new LineBoxIntersectBug());

    // Automatically run.
    run();
}

TestSuite::~TestSuite() {
    for(auto itTest = _tests.begin(); itTest != _tests.end(); ++itTest) {
        delete *itTest;
    }
}

void TestSuite::addTest(Test* test) {
    _tests.push_back(test);
}

void TestSuite::runSingle(Test* test) {
    _tests.clear();
    _tests.push_back(test);

    run();

    exit(0);
}

void TestSuite::run() {
    deque<Test*>::iterator itTest;
    int failed = 0;
    int passed = 0;

    cout << "Starting tests:" RULER << endl;

    for(itTest = _tests.begin(); itTest != _tests.end(); ++itTest) {
        Test* test = (*itTest);
        test->run();

        failed += test->getFailed();
        passed += test->getPassed();

        cout << "Test results for " << test->getName() << ":" << endl;
        cout << "    Passed: " << test->getPassed() << ", failed: " << test->getFailed() << "." << endl;

        const string trace = test->getTraceBuffer();
        if(!trace.empty()) {
            cout << trace;
        }
    }

    cout RULER;
    cout << "Final results: passed: " << passed << ", failed: " << failed << ".";
    if(failed != 0) {
        cout << endl << "There were some errors. It would be sensible to fix the first error, first." << endl <<
                "Since one error will probably cause any subsequent tests to yield errors, too.";
    }
    cout RULER << endl;
}