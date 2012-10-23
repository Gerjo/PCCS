#ifndef TREE_H
#define TREE_H
#include "GameObject.h"

using namespace phantom;

class Tree : public GameObject {
public:
    Tree();
    virtual bool canCollideWith(Composite* other);
};

#endif // !TREE_H