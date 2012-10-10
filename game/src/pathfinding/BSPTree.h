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
    BSPTree(float initialWidth, float initialHeight, float smallestSize, unsigned int collisionMaxPerSpace);
    virtual ~BSPTree();

    virtual void addComponent(Composite* component);
    virtual void update(const float& elapsed);

    void enableDebug();
    void disableDebug();

    void cleanPathfinding();

    Space* getSpaceAt(Vector3& location);
    vector<Space*>& getNeighbours(Space* location);
    void getEntitiesAt(vector<Entity*>& out, Vector3& location);

private:
    bool calculateCollision(Entity* a, Entity* b);

    bool _enableDebug;
    float _initialWidth;
    float _initialHeight;
    float _smallestSize;
    unsigned int _collisionMaxPerSpace;
    Space* _root;
};

#endif	/* BSPTREE_H */

