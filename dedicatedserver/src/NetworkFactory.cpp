#include "NetworkFactory.h"
#include <sharedlib/networking/NetworkRegistry.h>

GameObject* NetworkFactory::create(string objectName, string subname) {
    GameObject* gameobject = LightFactory::create(objectName, subname);

    // The server is the only one with authority to set
    // the "UID_network" field.
    gameobject->UID_network = gameobject->UID_local;
    gameobject->residence   = GameObject::ResidenceState::SERVER;

    NetworkRegistry::add(gameobject);

    return gameobject;
}
