#ifndef NETWORKFACTORY_H
#define	NETWORKFACTORY_H

#include "../CompileConfig.h"
#include "LightFactory.h"

class LIBEXPORT NetworkFactory {
public:
    static GameObject* create(string objectName);

};

#endif	/* NETWORKFACTORY_H */

