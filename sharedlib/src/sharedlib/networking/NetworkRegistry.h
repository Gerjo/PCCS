#ifndef REGISTRY_H
#define	REGISTRY_H

#include <iostream>
#include <phantom.h>
#include "../gameobjects/GameObject.h"
#include "UID.h"
#include "../CompileConfig.h"

using std::map;

class LIBEXPORT NetworkRegistry {
public:

    virtual ~NetworkRegistry();

    static void add(GameObject* gameobject);
    static void remove(GameObject* gameobject);
    static GameObject* get(const UID::Type& UID_network);
    static bool contains(const UID::Type& UID_network);

private:
    static NetworkRegistry* _INSTANCE;
    static void createInstance();

    NetworkRegistry();
    map<UID::Type, GameObject*> _registry;
};

#endif	/* REGISTRY_H */

