#include "Space.h"

Space::Space(float x, float y, float width, float height, float smallestSize) {
    g = 0.0f;
    h = 0.0f;
    astarParent     = nullptr;
    _area.origin.x  = x;
    _area.origin.y  = y;
    _area.size.x    = width;
    _area.size.y    = height;
    _smallestSize   = smallestSize;
    _left           = nullptr;
    _right          = nullptr;
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
        _left = nullptr;
        delete _right;
        _right = nullptr;
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

bool Space::isOptimalToWalkOn(Entity* entity) {
    // We don't check for the position intersection as this might be a "look ahead"
    // operation.

    // This space is empty, feel free to walk here. Trivial stuff.
    if(_entities.empty()) {
        return true;
    }

    const int limit = 10;

    // So let's ask people if we can walk here, we do this conditionally premature,
    // and force it when we're a leaf.
    if(_entities.size() < limit || isLeaf()) {

        for(Entity* test : _entities) {
            if(test->solidState & SolidStateBits::PLAYER) {
                return false;
            }
        }

        return true;
    }

    // One must recurse deeper.
    return false;
}

vector<Space*>& Space::getNeighboursOf(Space* whom, Entity* entity) {
    if(_area.intersect(whom->getArea())) {

        // Do we want to walk onto this space?
        if(isOptimalToWalkOn(entity)) {
            whom->addNeighbour(this);
            return whom->_neighbours;
        }

        // Recurse deeper into the BSP tree.
        if(!isLeaf()) {
            _left->getNeighboursOf(whom, entity);
            _right->getNeighboursOf(whom, entity);

            return whom->_neighbours;
        }
    }

    // We got a bit of a snafu here. There are no sensible neighbors
    // to walk on. I suppose that could be a use case.
    return whom->_neighbours;
}

void Space::clear() {
    g = h        = 0.0f;
    astarParent  = nullptr;
    isInOpenList = false;
    _neighbours.clear();

    if(_entities.empty()) {
        return;
    }

    _entities.clear();

    // Recurse deeper into the tree:
    if(!isLeaf()) {
        _left->clear();
        _right->clear();
    }
}

void Space::cleanPathfinding() {
    g = h        = 0.0f;
    astarParent  = nullptr;
    isInOpenList = false;
    _neighbours.clear();

    // Really naive assumption that if there are no entities, this would be an
    // A* node, and the children would not.
    if(_entities.empty()) {
        return;
    }

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
    return _left == nullptr;
}

Space* Space::getSpaceAtUsingHeuristic(Vector3& v, Entity* entity) {
    if(_area.contains(v)) {
        if(isOptimalToWalkOn(entity)) {
            return this;
        }

        if(!isLeaf()) {
            Space* left = _left->getSpaceAtUsingHeuristic(v, entity);

            if(left != nullptr) {
                return left;
            }

            return _right->getSpaceAtUsingHeuristic(v, entity);
        }
    }

    return nullptr;
}

Space* Space::getSpaceAt(Vector3& v) {

    // First empty space, thus also a leaf:
    if(_area.contains(v)) {
        if(_entities.empty()) {
            return this;
        }

        if(_entities.size() == 1 && !_entities.front()->isType("Tree")) {
            return this;
        }

        if(isLeaf()) {
            if(_area.contains(v)) {
                return this;
            } else {
                return nullptr;
            }
        }

        if(_left->getArea().contains(v)) {
            Space* left = _left->getSpaceAt(v);

            if(left != nullptr) {
                return left;
            }
        }

        return _right->getSpaceAt(v);
    }

    // Space not found.
    return nullptr;
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
            1.0f,
            1
        );

        g.rect(
            _area.origin.x + _area.size.x * 0.5f,
            _area.origin.y + _area.size.y * 0.5f - 5,
            1,
            1.0f
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