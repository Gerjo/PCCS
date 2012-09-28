#ifndef TREE_H
#define TREE_H
#include <core\Entity.h>

class Tree : public phantom::Entity
{
public:
    Tree();
    ~Tree();

    virtual void update(float elapsed);
private:
    void draw();
};

#endif // !TREE_H
