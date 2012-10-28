#include <map>

#include "NetworkRegistry.h"
#include "sharedlib/gameobjects/GameObject.h"
#include "sharedlib/SharedException.h"

NetworkRegistry* NetworkRegistry::_INSTANCE = 0;

void NetworkRegistry::createInstance() {
    if(NetworkRegistry::_INSTANCE == 0) {
        NetworkRegistry::_INSTANCE = new NetworkRegistry();
    }
}

NetworkRegistry::NetworkRegistry() {

}

NetworkRegistry::~NetworkRegistry() {

}

void NetworkRegistry::add(GameObject* gameobject) {
    if(gameobject->UID_network.empty()) {
        throw SharedException("NetworkRegistry::add() Adding components without a UID_network is not possible.");
    }

    UID::Type uid = gameobject->UID_network;

    if(!NetworkRegistry::contains(uid)) {
        NetworkRegistry::_INSTANCE->_registry.insert(std::pair<UID::Type, GameObject*>(uid, gameobject));

        //std::cout << "NetworkRegistry::add(" << gameobject->UID_network << ")" << std::endl;
    } else {
        std::cout << "NetworkRegistry::add(" << gameobject->UID_network << ") !! WARNING: Prevented adding object twice." << std::endl;
    }
}

void NetworkRegistry::remove(GameObject* gameobject) {
    if(gameobject->UID_network.empty()) {
        throw SharedException("NetworkRegistry::remove() Unable to remove gameobjects without a UID_network set.");
    }

    NetworkRegistry::createInstance();
    NetworkRegistry::_INSTANCE->_registry.erase(gameobject->UID_network);

    std::cout << "NetworkRegistry::remove(" << gameobject->UID_network << ")" << std::endl;
}

GameObject* NetworkRegistry::get(const UID::Type& UID_network) {
    if(NetworkRegistry::contains(UID_network)) {
        return NetworkRegistry::_INSTANCE->_registry[UID_network];
    }

    return 0;
}

bool NetworkRegistry::contains(const UID::Type& UID_network) {
    NetworkRegistry::createInstance();

    return NetworkRegistry::_INSTANCE->_registry.find(UID_network)
            !=
           NetworkRegistry::_INSTANCE->_registry.end();
}