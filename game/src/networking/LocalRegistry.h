#ifndef LOCALLOOKUP_H
#define	LOCALLOOKUP_H

#include <sharedlib/gameobjects/GameObject.h>
#include <sharedlib/networking/UID.h>

using std::string;
using std::map;

class LocalRegistry {
public:

    void add(GameObject* gameobject);

    void remove(GameObject* gameobject);
    void remove(const UID::Type uid);

    bool contains(GameObject* gameobject);
    bool contains(const UID::Type uid);

    GameObject* get(const UID::Type uid);

private:
    typedef std::pair<const UID::Type, GameObject*> Pair;
    map<const UID::Type, GameObject*> _map;
};

#endif	/* LOCALLOOKUP_H */

