#ifndef SPACE_H
#define	SPACE_H

#include <phantom.h>
#include <vector>

using namespace std;
using namespace phantom;

class Space {
public:
    Space(float x, float y, float width, float height, float smallestSize);
    ~Space();
    void insert(Entity* entity);
    void clear();
    bool contains(Entity* entity);
    void render(Graphics& g);

    Space* findSpace(Vector3& v);

    vector<Space*>& findNeighbours(Space* whom);
    void addNeighbour(Space* neighbour);

    void markBlack();
    void markPink();
    bool isLeaf();
    Box3& getArea();

    float getF() const {
        return g + h + h * 0.1;
    }

    Space* astarParent;
    bool  isInOpenList;

    float g; // Distance optimal path (steps taken so far). g = parent.g + 1;
	float h; // Heuristic for this node (diagonal, euler, manhattan etc)
private:
    float _scale;
    Box3 _area;
    Space* _left;
    Space* _right;
    deque<Entity*> _entities;
    float _smallestSize;
    bool _isBlack;
    bool _isPink;
    vector<Space*> _neighbours;
};

struct CompareShapesAstar {
    bool operator() (const Space* a, const Space * b) {
        return a->getF() > b->getF();
    }
};

#endif	/* SPACE_H */

