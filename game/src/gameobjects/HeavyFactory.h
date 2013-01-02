#ifndef HEAVYFACTORY_H
#define	HEAVYFACTORY_H

#include <string>

#include <sharedlib/gameobjects/GameObject.h>

using namespace std;

class HeavyFactory {
public:
    static GameObject* create(string objectName, string subname = "") {
        if(INSTANCE == 0) {
            INSTANCE = new HeavyFactory();
        }
        return INSTANCE->createFromString(objectName, subname);
    }

private:
    HeavyFactory();
    HeavyFactory(const HeavyFactory& origin);
    GameObject* createFromString(string objectName, string subname);
    static HeavyFactory* INSTANCE;
    Data _enemies;
};


#endif	/* HEAVYFACTORY_H */

