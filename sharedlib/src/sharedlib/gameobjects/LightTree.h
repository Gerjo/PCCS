#ifndef TREE_H
#define TREE_H
#include "GameObject.h"

using namespace phantom;

class LightTree : public GameObject {
public:
    LightTree();
    virtual bool canCollideWith(Composite* other);
};

#endif // !TREE_H
