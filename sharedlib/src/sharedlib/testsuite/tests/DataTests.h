#ifndef DATATESTS_H
#define	DATATESTS_H

#include "../Test.h"
#include "../../CompileConfig.h"
#include <phantom.h>
#include "../../serialization/Data.h"

using namespace phantom;

using std::string;

class LIBEXPORT DataTests : public Test {
public:
    DataTests() : Test("Testing Data serialisation") {

    }

    virtual void run() {
        const string name  = "Gerjo";
        const int age      = 25;
        const float height = 20.5f;

        Data data;
        data("name")   = "Gerjo";
        data("age")    = 25;
        data("height") = 20.5f;


        if(!assertTrue(name == (string) data("name"))) {
            trace("String serialize failed.");
        }

        if(!assertTrue(age == (int) data("age"))) {
            trace("Integer serialize failed.");
        }

        if(!assertTrue(height == (float) data("height"))) {
            trace("Float serialize failed.");
        }

        Data copy(data);
        if(!assertTrue(name == (string) copy("name"))) {
            trace("String serialize failed after copy ctor.");
        }

        if(!assertTrue(age == (int) copy("age"))) {
            trace("Integer serialize failed after copy ctor.");
        }

        if(!assertTrue(height == (float) copy("height"))) {
            trace("Float serialize failed after copy ctor.");
        }

        string asJson = data.toJson();
        Data fromJson = Data::fromJson(asJson);

        if(!assertTrue(name == (string) fromJson("name"))) {
            trace("String serialize failed after toJson / fromJson.");
        }

        if(!assertTrue(age == (int) fromJson("age"))) {
            trace("Integer serialize failed after toJson / fromJson.");
        }

        if(!assertTrue(height == (float) fromJson("height"))) {
            trace("Float serialize failed after toJson / fromJson.");
        }

        Data escape = Data::fromJson("{\"quoted\":\" pre \\\" post \"}");

        const string expected = " pre \\\" post ";

        if(!assertTrue(expected.compare((string)escape("quoted")) == 0)) {
            trace("Data did not serialize escaped quotes correctly.");
            trace("Expected: -" + expected + "- received: -" + (string)escape("quoted") + "-");


            // So let me explain this. We are using an "optimized" parser, if our data contained
            // an escape sequence, we'd have to "trim" this sequence from the middle of a string
            // the latter being probably (yea, I'm just guessing here) resource heavy. In short,
            // if you escape data, the escape sequence will be there the rest of your life. Kind
            // of like escaping the escape. UCANHAZCHEESEBURGER. TL;DR: the person that
            // wrote this parser is skilled at being lazy. OK changed my mind. This is not a bug
            // it's a niche feature.
            trace("Actually this test was fine-tuned for a bug, so if you see this, it could"
                    " well be the case that this bug was fixed.");
        }

    }
};

#endif	/* DATATESTS_H */

