#include <cstdlib>
#include <iostream>
#include <sstream>
#include <map>
#include <string>
#include "core/GameHub.h"

#include <sharedlib/serialization/Data.h>

using namespace std;

int main(int argc, char** argv) {
    //GameHub server;

    double start = phantom::Util::getTime();

    Data sub;
    sub("age")  = 3;
    sub("name") = "gerjo";
    sub("surname") = "meier";
    sub("length")  = 206;

    sub("bla1")("aa") = 123;
    sub("bla1")("ww")("www") = 234;
    sub("bla1")("bb") = 123;
    sub("bla1")("cc") = 123;
    sub("bla1")("ww")("ww")("ww")("ww") = 123;

    sub("test")("test") = "123";
    float age = sub("test")("test");

    cout << age << endl;

    cout << "------" << endl;
    string str2 = sub.toJson();
    //cout << str2 << endl;


    Data sub2;
    sub2.parseJson("{\"name\": \"gerard\",\"age\": \"12\",\"address\": {\"street\": \"Simon Stevinweg\",\"postal\": \"1222st\"}}");

    cout << "Size of one set: " << sizeof(sub) << endl;
    cout << endl << "delay: " << (phantom::Util::getTime() - start) << endl;

    cout << sub.toJson() << endl;

    return 0;
}
