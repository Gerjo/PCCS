#ifndef OBJECTFACTORY_H
#define	OBJECTFACTORY_H

#include <phantom.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "GameException.h"
#include "gameobjects/GameObject.h"

using namespace phantom;
using namespace std;

class ObjectFactory {
public:
    static ObjectFactory* GetInstance();

    GameObject* createFromString(string objectName);


    template<class T>
    T createFromStringT(string objectName) {
        return static_cast<T>(createFromString(objectName));
    }

private:
    ObjectFactory();
    ObjectFactory(const ObjectFactory& origin);

    static ObjectFactory* INSTANCE;
};

#endif	/* OBJECTFACTORY_H */

