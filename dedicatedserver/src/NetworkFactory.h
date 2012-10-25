#ifndef NETWORKFACTORY_H
#define	NETWORKFACTORY_H

#include <sharedlib/gameobjects/LightFactory.h>

class LIBEXPORT NetworkFactory {
public:
    static GameObject* create(string objectName);

};

#endif	/* NETWORKFACTORY_H */

