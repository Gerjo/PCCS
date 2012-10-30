#ifndef HEAVYFACTORY_H
#define	HEAVYFACTORY_H

#include <sharedlib/gameobjects/LightFactory.h>


// All heavy gameobjects:
#include "HeavyTree.h"
#include "HeavySoldier.h"
#include "HeavyBullet.h"
#include "HeavyWeapon.h"

using namespace phantom;
using namespace std;

class HeavyFactory {
public:
    static GameObject* create(string objectName) {
        if(INSTANCE == 0) {
            INSTANCE = new HeavyFactory();
        }

        return INSTANCE->createFromString(objectName);
    }

private:
    HeavyFactory();
    HeavyFactory(const HeavyFactory& origin);
    GameObject* createFromString(string objectName);
    static HeavyFactory* INSTANCE;
};


#endif	/* HEAVYFACTORY_H */

