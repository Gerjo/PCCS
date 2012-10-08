#ifndef BSPTREE_H
#define	BSPTREE_H

#include <phantom.h>
#include "Space.h"
#include <vector>
#include "../GameException.h"

using namespace phantom;
using namespace std;

class BSPTree : public Layer  {
public:
    BSPTree(float initialWidth, float initialHeight, float smallestSize);
    virtual ~BSPTree();

    virtual void addComponent(Composite* component);
    virtual void update(const float& elapsed);

    void enableDebug();
    void disableDebug();

    Space* getSpaceAt(Vector3& location);
    vector<Space*>& getNeighbours(Space* location);

private:
    bool _enableDebug;
    float _initialWidth;
    float _initialHeight;
    float _smallestSize;
    Space* _root;
};

#endif	/* BSPTREE_H */

