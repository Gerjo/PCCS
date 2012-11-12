#ifndef TREE_H
#define TREE_H
#include "GameObject.h"
#include <sharedlib/serialization/Serializable.h>
#include "../CompileConfig.h"

using namespace phantom;

class LIBEXPORT LightTree : public GameObject {
public:
    LightTree();
};

#endif // !TREE_H
