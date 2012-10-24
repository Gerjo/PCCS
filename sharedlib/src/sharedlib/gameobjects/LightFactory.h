#ifndef OBJECTFACTORY_H
#define	OBJECTFACTORY_H

#include <phantom.h>
#include <string>
#include <algorithm>

#include "GameObject.h"
#include "../SharedException.h"

// All lightweight gameobjects:
#include "LightTree.h"
#include "LightSoldier.h"

using namespace phantom;
using namespace std;

class LightFactory {
public:
    static GameObject* create(string objectName) {
        if(INSTANCE == 0) {
            INSTANCE = new LightFactory();
        }

        return INSTANCE->createFromString(objectName);
    }
private:
    LightFactory();
    LightFactory(const LightFactory& origin);
    GameObject* createFromString(string objectName);
    static LightFactory* INSTANCE;
};

#endif	/* OBJECTFACTORY_H */
