#include "core/GameHub.h"

#include <sharedlib/networking/networking.h>
#include <sharedlib/serialization/Data.h>

#include <iostream>
using namespace std;

int main(int argc, char** argv) {
    GameHub server;

    /*
    Data data;

    data("it-an-int") = 23;
    data("float") = 23.23f;
    data("some")("obscure")("nested")("1") = "hello!";
    data("some")("obscure")("nested")("2") = "hello!!";
    data("some")("obscure")("nested")("3") = "hello!!!";
    data("some")("obscure")("nested")("4") = "hello!!!!";
    data("some")("obscure")("nested")("5") = "hello!!!!!";
    data("some")("obscure")("someint") = 23;

    // To json:
    string json = data.toJson();

    // Or create from json:
    Data parsed;
    parsed.parseJson(json);

    // Copy semantics work:
    Data clone = parsed;


    int meh2 = clone("it-an-int");
    float meh2 = clone("float");


    for(Data::KeyValue pair : data) {
        // For in range loops, work too!
    }*/

    return 0;
}
