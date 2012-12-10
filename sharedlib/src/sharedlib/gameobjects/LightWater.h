#ifndef LIGHTWATER_H
#define LIGHTWATER_H
#include "GameObject.h"
#include <sharedlib/serialization/Serializable.h>
#include "../CompileConfig.h"

using namespace phantom;

class LIBEXPORT LightWater : public GameObject {
public:
    LightWater();
};

#endif
