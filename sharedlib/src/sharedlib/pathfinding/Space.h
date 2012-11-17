#ifndef SPACE_H
#define	SPACE_H

#include <phantom.h>
#include <vector>
#include "../CompileConfig.h"

using namespace std;
using namespace phantom;

class LIBEXPORT Space {
public:
    Space(float x, float y, float width, float height, const unsigned smallestSize);
    ~Space();
    void insert(Entity* entity);
    void remove(Entity* entity);
    void clear();
    bool contains(Entity* entity);
    void render(Graphics& g);
    vector<Entity*>& getEntities();
    Space* getSpaceAt(Vector3& v);
    Space* getSpaceAtUsingHeuristic(Vector3& v, Entity* entity);
    vector<Space*>& getNeighboursOf(Space* whom, Entity* entity = nullptr);
    void addNeighbour(Space* neighbour);

    bool isLeaf();
    Box3& getArea();
    Vector3 getCenter();
    float getF() const {
        return g + h + h * 0.1f;
    }

    Space* astarParent;
    bool  isInOpenList;

    float g; // Distance optimal path (steps taken so far). g = parent.g + 1;
	float h; // Heuristic for this node (diagonal, euler, manhattan etc)

    void getCollisionSpaces(vector<Space*>& out, const unsigned int& maxPerSpace);
    void cleanPathfinding();

private:
    static unsigned long long count;
    bool isOptimalToWalkOn(Entity* entity = nullptr);

    void recursivelyInsert(Entity* entity);
    void disburse();
    bool _hasDisbursed;

    Box3 _area;
    Space* _left;
    Space* _right;
    vector<Entity*> _entities;
    vector<Space*> _neighbours;
    const unsigned char _childLimit;
    const unsigned _smallestSize;
};

struct LIBEXPORT CompareShapesAstar {
    bool operator() (const Space* a, const Space * b) {
        return a->getF() > b->getF();
    }
};

#endif	/* SPACE_H */

