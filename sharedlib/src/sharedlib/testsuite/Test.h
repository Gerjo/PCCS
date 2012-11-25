#ifndef TEST_H_NIMBLE
#define	TEST_H_NIMBLE

#include <string>
#include <sstream>
#include <cstring>
#include <iostream>
#include "../CompileConfig.h"

#include <phantom.h>
using namespace phantom;
using namespace std;

class LIBEXPORT Test {
    public:
        Test(string name);
        string getName();

        virtual void run(void) = 0;

        int getFailed();
        int getPassed();

        const std::string getTraceBuffer();

    private:
        string _name;
        int _failed;
        int _passed;

        bool testFailed();
        bool testSuccess();

        std::stringstream _traceBuffer;

    protected:
        bool assertTrue(const bool condition);
        bool assertFalse(const bool condition);
        bool assertEquals(const string a, const string b);
        bool assertEquals(const char* a, const char* b, const int len);
        bool assertEquals(const Vector3& v, const float& x, const float& y, const float& z = 0.0f);

        void trace(string data);
        void trace(string data, string data1);
        void trace(string data, string data1, string data2);
};

#endif	/* TEST_H_NIMBLE */
