#ifndef BSPTREE_H
#define	BSPTREE_H

#include <phantom.h>
#include "Space.h"

class BSPTree : public phantom::Layer  {
public:
    BSPTree(float initialWidth, float initialHeight, float smallestSize);
    virtual ~BSPTree();

    void update(const float& elapsed);

private:
    float _initialWidth;
    float _initialHeight;
    float _smallestSize;
    Space* _root;
};

#endif	/* BSPTREE_H */

