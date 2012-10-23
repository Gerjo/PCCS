#ifndef TREE_H
#define TREE_H
#include "GameObject.h"
#include <sharedlib/serialization/Serializable.h>

using namespace phantom;

class LightTree : public GameObject {
public:
    LightTree();
    virtual bool canCollideWith(Composite* other);

    virtual void fromData(Data& data);
    virtual void toData(Data& data);
};

#endif // !TREE_H
