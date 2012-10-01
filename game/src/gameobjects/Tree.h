#ifndef TREE_H
#define TREE_H
#include <core/Entity.h>

using namespace phantom;

class Tree : public Entity
{
public:
    Tree();
    ~Tree();

    virtual void update(float elapsed);
private:
    void draw();
};

#endif // !TREE_H
