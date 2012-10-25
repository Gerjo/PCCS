#ifndef SPACE_H
#define	SPACE_H

#include <phantom.h>
#include <vector>
#include "../CompileConfig.h"

using namespace std;
using namespace phantom;

class Space;

struct LIBEXPORT PathfindingDataBuffer {
public:
    PathfindingDataBuffer(Space* space) : g(0), h(0) {
        _space = space;
    }

    float g, h;

    float getF() const {
        return g + h + h * 0.1f;
    }

private:
    Space* _space;
};

class LIBEXPORT Space {
public:
    Space(float x, float y, float width, float height, float smallestSize);
    ~Space();
    void insert(Entity* entity);
    void remove(Entity* entity);
    void clear();
    bool contains(Entity* entity);
    void render(Graphics& g);
    vector<Entity*>& getEntities();
    Space* getSpaceAt(Vector3& v);
    vector<Space*>& getNeighboursOf(Space* whom);
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
    float _scale;
    Box3 _area;
    Space* _left;
    Space* _right;
    vector<Entity*> _entities;
    float _smallestSize;
    vector<Space*> _neighbours;
};

struct LIBEXPORT CompareShapesAstar {
    bool operator() (const Space* a, const Space * b) {
        return a->getF() > b->getF();
    }
};

#endif	/* SPACE_H */

