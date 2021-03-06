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

void NetworkRegistry::dump(void) {
    NetworkRegistry::createInstance();

    for(std::pair<UID::Type, GameObject*> pair : _INSTANCE->_registry) {
        cout << "Key: " << pair.first << endl;
    }
}

void NetworkRegistry::destroy() {
    delete NetworkRegistry::_INSTANCE;
    NetworkRegistry::_INSTANCE = 0;
}

void NetworkRegistry::add(GameObject* gameobject) {
    if(gameobject->UID_network.empty()) {
        throw SharedException("NetworkRegistry::add() Adding components without a UID_network is not possible.");
    }

    UID::Type uid = gameobject->UID_network;

    if(!NetworkRegistry::contains(uid)) {
        NetworkRegistry::_INSTANCE->_registry.insert(std::pair<UID::Type, GameObject*>(uid, gameobject));
#ifdef _DEBUG
        std::cout << "NetworkRegistry::add(" << gameobject->UID_network << ")" << std::endl;
#endif
    } else {
        std::cout << "NetworkRegistry::add(" << gameobject->UID_network << ") !! WARNING: Prevented adding object twice." << std::endl;
    }
}

void NetworkRegistry::remove(GameObject* gameobject) {
    if(gameobject->UID_network.empty()) {
        //cout << "WARNING: Removing a " << gameobject->getType() << " without UID_network." << endl;
        return;
    }

    if(NetworkRegistry::contains(gameobject->UID_network)) {
        NetworkRegistry::_INSTANCE->_registry.erase(gameobject->UID_network);
        //std::cout << "NetworkRegistry::remove(" << gameobject->UID_network << ")" << std::endl;
    } else {
        std::cout << "!! WARNING NetworkRegistry::remove(" << gameobject->UID_network << ") not found." << std::endl;
    }

}

GameObject* NetworkRegistry::get(const UID::Type& UID_network) {
    //std::cout << "NetworkRegistry::get(" << UID_network << ")" << std::endl;
    if(NetworkRegistry::contains(UID_network)) {
        GameObject* gob = NetworkRegistry::_INSTANCE->_registry.at(UID_network);

        return gob;
    }

    return nullptr;
}

bool NetworkRegistry::contains(const UID::Type& UID_network) {
    NetworkRegistry::createInstance();

    return NetworkRegistry::_INSTANCE->_registry.find(UID_network)
            !=
           NetworkRegistry::_INSTANCE->_registry.end();
}