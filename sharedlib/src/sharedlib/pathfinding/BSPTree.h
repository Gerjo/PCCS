#ifndef BSPTREE_H
#define	BSPTREE_H

#include <phantom.h>
#include "Space.h"
#include <vector>
#include "../SharedException.h"
#include "../CompileConfig.h"
#include "SolidStateBits.h"

using namespace phantom;
using namespace std;

class Pathfinding;

class LIBEXPORT BSPTree : public Layer  {
public:
    BSPTree(float initialWidth, float initialHeight, float smallestSize, unsigned int collisionMaxPerSpace);
    virtual ~BSPTree();

    virtual void addComponent(Composite* component);
    virtual void update(const Time& time);
    virtual void removeComponent(Composite* who);
    virtual void destroyComponent(Composite* who);

    void enableDebug();
    void disableDebug();

    void cleanPathfinding();

    Space* getSpaceAt(Vector3& location);
    vector<Entity*> getEntitiesFromBox(Box3* location);
    vector<Space*>& getNeighbours(Space* location, Entity* entity);
    void getEntitiesAt(vector<Entity*>& out, Vector3& location);

    Pathfinding* pathfinding;

private:
    bool calculateCollision(Entity* a, Entity* b);

    bool _enableDebug;
    float _initialWidth;
    float _initialHeight;
    float _smallestSize;
    unsigned int _collisionMaxPerSpace;
    Space* _root;
    bool _isTreeIterating;

    // The sadness is unbearable :(
    deque<Composite*> _destroyUs;
    deque<Composite*> _removeUs;
};

#endif	/* BSPTREE_H */

