#include "TestSuite.h"

#define RULER  << endl << "----------------------------------------" << endl

#include "tests/TestingTests.h"

TestSuite::TestSuite() {
    addTest(new TestingTests());


    // Automatically run.
    run();
}

TestSuite::~TestSuite() {
    for(deque<Test*>::iterator itTest = _tests.begin(); itTest != _tests.end(); ++itTest) {
        delete (*itTest);
    }
}

void TestSuite::addTest(Test* test) {
    _tests.push_back(test);
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
    cout << "Final results: passed: " << passed << ", failed: " << failed << "." << endl << endl;
}