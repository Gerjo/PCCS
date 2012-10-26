#ifndef NETWORKFACTORY_H
#define	NETWORKFACTORY_H

#include <sharedlib/gameobjects/LightFactory.h>

// This class is just a wrapper around LightFactory. Creating a wrapper
// solves the "inheritance" problem with static members.
class LIBEXPORT NetworkFactory {
public:
    static GameObject* create(string objectName);

};

#endif	/* NETWORKFACTORY_H */

