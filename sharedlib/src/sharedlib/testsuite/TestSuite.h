#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <iostream>
#include <deque>
#include "Test.h"

using namespace std;


class TestSuite {
    public:
        TestSuite();
        ~TestSuite();
        void run();
        void addTest(Test* test);

    private:
        deque<Test*> _tests;
};


#endif	/* TESTSUITE_H */

