#include "Test.h"


Test::Test(string name) : _name(name) {
    _failed = 0;
    _passed = 0;
}

string Test::getName() {
    return _name;
}

int Test::getFailed() {
    return _failed;
}

int Test::getPassed() {
    return _passed;
}

bool Test::testFailed() {
    _failed++;
    return false;
}

bool Test::testSuccess() {
    _passed++;
    return true;
}

bool Test::assertTrue(const bool condition) {
    if(condition == true) {
        return testSuccess();
    }

    return testFailed();
}

bool Test::assertFalse(const bool condition) {
    if(condition == false) {
        return testSuccess();
    }

    return testFailed();
}

bool Test::assertEquals(const string a, const string b) {
    if(a.compare(b) == 0) {
        return testSuccess();
    }

    return testFailed();
}

bool Test::assertEquals(const char* a, const char* b, const int len) {

    for(int i = 0; i < len; ++i) {
        //std::cout << (int)*a;
        //std::cout <<  " vs ";
        //std::cout << (int)*b;
        //std::cout.write(b, 1);

        if(*a++ != *b++) {
            return testFailed();
        }
    }

    return testSuccess();
}

bool Test::assertEquals(const Vector3& v, const float& x, const float& y, const float& z) {
    if(v.x == x, v.y == y, v.z == z) {
        return testSuccess();
    }

    return testFailed();
}

void Test::trace(string data) {
    _traceBuffer << "    - Error " << data << endl;
}

void Test::trace(string data, string data1) {
    _traceBuffer << "    - Error " << data << " " << data1 << endl;
}

void Test::trace(string data, string data1, string data2) {
    _traceBuffer << "    - Error " << data << " " << data1 << " " << data2 << endl;
}

const std::string Test::getTraceBuffer() {
    return _traceBuffer.str();
}
