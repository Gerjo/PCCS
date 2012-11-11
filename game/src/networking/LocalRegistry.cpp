
#include "LocalRegistry.h"

#include <iostream>
using namespace std;

void LocalRegistry::add(GameObject* gameobject) {
    _map.insert(Pair(gameobject->UID_local, gameobject));

    cout << "inserted " << gameobject->UID_local << endl;
}

void LocalRegistry::remove(GameObject* gameobject) {
   remove(gameobject->UID_local);
}

void LocalRegistry::remove(const UID::Type uid) {
    if(contains(uid)) {
        _map.erase(uid);
    }
}

bool LocalRegistry::contains(GameObject* gameobject) {
    return contains(gameobject->UID_local);
}

bool LocalRegistry::contains(const UID::Type uid) {
    return _map.find(uid) != _map.end();
}

GameObject* LocalRegistry::get(const UID::Type uid) {
    if(contains(uid)) {
        return _map.at(uid);
    }

    return nullptr;
}
