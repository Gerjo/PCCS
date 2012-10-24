#ifndef HEAVYTREE_H
#define	HEAVYTREE_H


#include <sharedlib/gameobjects/LightTree.h>

using namespace phantom;

class HeavyTree : public LightTree {
public:
    HeavyTree();
    virtual ~HeavyTree();
    virtual void paint(void);

private:

};

#endif	/* HEAVYTREE_H */

