#ifndef SPACE_H
#define	SPACE_H

#include <phantom.h>

using namespace std;
using namespace phantom;

class Space {
public:
    Space(float x, float y, float width, float height, float smallestSize);
    void insert(Entity* entity);
    void clear();
    bool contains(Entity* entity);
    void render(Graphics& g);

    Space* findLeaf(Vector3& v);

    void mark();
    Box3& getArea();
private:
    float _scale;
    Box3 _area;
    Space* _left;
    Space* _right;
    deque<Entity*> _entities;
    float _smallestSize;
    bool _isMarked;
    bool isLeaf();
};

#endif	/* SPACE_H */

