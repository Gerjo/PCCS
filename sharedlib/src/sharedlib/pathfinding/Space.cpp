#include "Space.h"

Space::Space(float x, float y, float width, float height, float smallestSize) {
    g = 0;
    h = 0;
    astarParent     = 0;
    _area.origin.x  = x;
    _area.origin.y  = y;
    _area.size.x    = width;
    _area.size.y    = height;
    _smallestSize   = smallestSize;
    _left           = 0;
    _right          = 0;
    float scale     = 0.5f;
    isInOpenList    = false;

    if(width > _smallestSize || height > _smallestSize) {
        float halfWidth  = width * scale;
        float halfHeight = height * scale;

        if(width > height) {
            _left  = new Space(x, y, halfWidth, height, _smallestSize);
            _right = new Space(x + halfWidth, y, halfWidth, height, _smallestSize);
        } else {
            _left  = new Space(x, y, width, halfHeight, _smallestSize);
            _right = new Space(x, y + halfHeight, width, halfHeight, _smallestSize);
        }
    }
}

Space::~Space() {
    if(!isLeaf()) {
        delete _left;
        delete _right;
    }
}

void Space::insert(Entity* entity) {
    _entities.push_back(entity);

    if(!isLeaf()) {
        bool added = false;
        if(_left->contains(entity)) {
            _left->insert(entity);
            added = true;
        }

        if(_right->contains(entity)) {
            _right->insert(entity);
            added = true;
        }

        if(!added) {
            //cout << "BSPTree bounding box containment error? Object: " << entity->getType() << endl;
            //cout << " " << entity->getBoundingBox().toString() << endl;
        }
    }
}

vector<Space*>& Space::getNeighboursOf(Space* whom) {
    if(_area.intersect(whom->getArea())) {
        if(_entities.empty()) {
            //if(whom != this) {
                whom->addNeighbour(this);
            //}
        } else if(_entities.size() == 1  && // && whom != this
                !_entities.front()->isType("Tree")
                ) {
            //cout << "hack " << _entities.front()->getType() << endl;
            whom->addNeighbour(this);
        } else {
            if(!isLeaf()) {
                // NB: disabled intersect test, the test takes longer than
                // a full itereation. Perhaps if the tree is bigger, this will
                // change. -- Gerjo

                //if(_left->getArea().intersect(whom->getArea())) {
                    _left->getNeighboursOf(whom);
                //}
                //if(_right->getArea().intersect(whom->getArea())) {
                    _right->getNeighboursOf(whom);
                //}
            }
        }
    }

    return whom->_neighbours;
}

void Space::clear() {
    if(_entities.empty())
        return;
    _entities.clear();

    if(!isLeaf()) {
        _left->clear();
        _right->clear();
    }
}

void Space::cleanPathfinding() {
    g = 0;
    h = 0;
    astarParent  = 0;
    isInOpenList = false;
    _neighbours.clear();

    if(!isLeaf()) {
        _left->cleanPathfinding();
        _right->cleanPathfinding();
    }
}

bool Space::contains(Entity* entity) {
    return _area.intersect(entity->getBoundingBox());
    //return _area.contains(entity->getPosition());
}


bool Space::isLeaf() {
    return _left == 0;
}

Space* Space::getSpaceAt(Vector3& v) {
    // First empty space, thus also a leaf:
    if(_area.contains(v) && _entities.empty()) {
        return this;
    }

    if(_entities.size() == 1 && !_entities.front()->isType("Tree")) {
        return this;
    }

    if(isLeaf()) {
        if(_area.contains(v)) {
            return this;
        } else {
            return 0;
        }
    }

    if(_left->getArea().contains(v)) {
        Space* left = _left->getSpaceAt(v);

        if(left != 0) {
            return left;
        }
    }

    return _right->getSpaceAt(v);
}

Box3& Space::getArea() {
    return _area;
}

void Space::addNeighbour(Space* neighbour) {
    _neighbours.push_back(neighbour);
}

void Space::render(Graphics& g) {
    if(_entities.empty() || isLeaf()) {
        g.beginPath();

        if(_entities.size() > 1) {
            g.setFillStyle(Color(127, 0, 0, 60));
        } else {
            g.setFillStyle(Color(127, 127, 127, 20));
        }

        g.rect(
            _area.origin.x + 1,
            _area.origin.y + 1,
            _area.size.x - 2,
            _area.size.y - 2
        );

        g.fill();

        g.beginPath();

        g.setFillStyle(Colors::BLACK);

        g.rect(
            _area.origin.x + _area.size.x * 0.5f - 5,
            _area.origin.y + _area.size.y * 0.5f,
            10,
            1
        );

        g.rect(
            _area.origin.x + _area.size.x * 0.5f,
            _area.origin.y + _area.size.y * 0.5f - 5,
            1,
            10
        );

        g.fill();

        if(!isLeaf()) {
            return;
        }
    }

    if(!isLeaf()) {
        _left->render(g);
        _right->render(g);
    }
}

void Space::getCollisionSpaces(vector<Space*>& out, const unsigned int& maxPerSpace) {
    // Tough love, if you're alone in your space, you won't get a collision
    // test at all. :(

    if(_entities.size() > 1) {

        if(!isLeaf() && _entities.size() >= maxPerSpace) {
            _left->getCollisionSpaces(out, maxPerSpace);
            _right->getCollisionSpaces(out, maxPerSpace);

            return;
        }

        out.push_back(this);
    }
}

vector<Entity*>& Space::getEntities() {
    return _entities;
}

Vector3 Space::getCenter() {
    Vector3 center(
    _area.origin.x + _area.size.x * 0.5f,
    _area.origin.y + _area.size.y * 0.5f,
    0.0f);

    return center;
}

void Space::remove(Entity* entity) {
    for(auto it = _entities.begin(); it != _entities.end(); ++it) {
        if(*it == entity) {
            _entities.erase(it);
            break;
        }
    }

    if(_right->contains(entity)) {
        _right->remove(entity);
    }

    if(_left->contains(entity)) {
        _left->remove(entity);
    }
}