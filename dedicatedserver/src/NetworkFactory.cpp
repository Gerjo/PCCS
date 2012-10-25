#include "NetworkFactory.h"

GameObject* NetworkFactory::create(string objectName) {
    GameObject* gameobject = LightFactory::create(objectName);

    // The server is the only one with authority to set
    // the "UID_network" field.
    gameobject->UID_network = gameobject->UID_local;

    return gameobject;
}
