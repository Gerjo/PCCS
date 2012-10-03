#ifndef TREE_H
#define TREE_H
#include "../gameobjects/GameObject.h"

using namespace phantom;

class Tree : public GameObject {
public:
    Tree();
    ~Tree();

    virtual void update(float elapsed);
private:
    void draw();
};

#endif // !TREE_H
